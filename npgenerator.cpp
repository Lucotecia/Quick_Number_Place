#include "npgenerator.h"

NPGenerator::NPGenerator(int r,QObject *parent) :
    QObject(parent),
    rest(r),
    engine_ptr(new std::mt19937((*seed)()))
{}

NPGenerator::~NPGenerator(){
    delete engine_ptr;
}

void NPGenerator::generate(){
    init_board(answer);
    fill_answer();
    while (true)
    {
        if (hole())
            break;
    }
}

std::mt19937* NPGenerator::seed = new std::mt19937(static_cast<unsigned int>(std::time(nullptr)));

QString NPGenerator::get_problem(){
    QString s = "";
    int i;
    for (i = 0; i < 81;i++){
        s += QString::number(get_number(problem,i));
    }
    return s;
}

QString NPGenerator::get_answer(){
    QString s = "";
    int i;
    for (i = 0; i < 81; i++){
        s += QString::number(get_number(answer, i));
    }
    return s;
}

void NPGenerator::init_board(int *board){
    int i;
    for(i=0;i<81;i++){
        board[i] = 1022;
    }
}

void NPGenerator::copy_board(int* board1,int* board2){//1←2
    int i;
    for(i=0;i<81;i++){
        board1[i] = board2[i];
    }
}

void NPGenerator::eliminate(int* board, const int index, const int n){
    int x = index%9, y = index/9;
    int i, xo = (x/3)*3, yo = (y/3)*3;
    int bitn = ~(1<<n);
    for(i=0;i<9;i++){
        board[(yo+i/3)*9+xo+i%3] &= bitn;
        board[i*9+x] &= bitn;
        board[y*9+i] &= bitn;
    }
    board[index] += (~bitn);
}

int NPGenerator::check_board(int* board){//何も入らないマスが生じたなら0,チェックによって何も変わらなければ1,変われば2,全マス確定すれば3
    int i,k,count,flag,dcount,n;
    do{
        flag=1;
        dcount = 0;
        for(i=0;i<81;i++){
            count = 0;
            for(k=1;k<=9;k++){
                if(board[i]&(1<<k)){
                    n = k;
                    count++;
                }
            }
            if(count == 0){
                //printf("0");
                return 0;
            }else if(count == 1){
                if(!(board[i]&1)){
                    board[i]++;
                    flag = 2;
                    eliminate(board,i,n);
                }
                dcount++;
            }
        }
        if(dcount == 81){
            //printf("3");
            return 3;
        }
    }while(flag==2);
    //printf("%d", flag);
    return flag;
}

int NPGenerator::get_number(int* board, const int index){
    int k;
    if(!(board[index]&1)){
        return 0;
    }
    for(k=1;k<=9;k++){
        if(board[index]&(1<<k)){
            return k;
        }
    }
}

/*void NPGenerator::print_board(int* board){
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            printf("%d",get_number(board,j+9*i));
            if(j==2||j==5){
                printf("|");
            }else if(j==8){
                printf("\n");
            }else{
                printf(" ");
            }
        }
        if(i==2||i==5){
            printf("-----+-----+-----\n");
        }
    }
    printf("\n");
}
*/
bool NPGenerator::fill_answer(){
    int flag = check_board(answer),matindex,i,j,k,r,tmp;
    int randomorder[9];
    int cp[81];
    if(flag == 3){
        copy_board(problem,answer);
        return true;
    }else if(flag == 0){
        return false;
    }
    for(matindex=0;matindex<81;matindex++){
        i = matindex/9;
        j = matindex%9;
        if(!(answer[matindex]&1)){
            break;
        }
    }
    for(k=0;k<9;k++){
        randomorder[k] = k+1;
    }
    for(k=0;k<9;k++){
        r = (*engine_ptr)()%9;
        tmp = randomorder[r];
        randomorder[r] = randomorder[k];
        randomorder[k] = tmp;
    }
    for(k=0;k<9;k++){
        if(answer[matindex]&(1<<randomorder[k])){
            copy_board(cp,answer);
            set_number(answer,matindex,randomorder[k]);
            if(fill_answer()){
                return true;
            }else{
                copy_board(answer,cp);
            }
        }
    }
    return false;
}

void NPGenerator::set_number(int* board, const int index, const int number){
    board[index] = (1<<number)+1;
    eliminate(board,index,number);
}

bool NPGenerator::hole(){
    int i,tmp,list[81],rnd;
    for(i=0;i<81;i++){
        list[i] = i;
    }
    do{
        for(i=0;i<81;i++){
            rnd = (*engine_ptr)()%81;
            tmp = list[i];
            list[i] = list[rnd];
            list[rnd] = tmp;
        }
        init_board(problem);
        for(i=0;i<rest;i++){
            set_number(problem,list[i],get_number(answer,list[i]));
        }
    }while(!issolvable());
    return true;
}

bool NPGenerator::issolvable(){
    int tmp[81];
    copy_board(tmp,problem);
    if(!solve_min(tmp)){
        return false;
    }
    if(!equals(minans,answer)){
        return false;
    }
    copy_board(tmp,problem);
    if(!solve_max(tmp)){
        return false;
    }
    if(!equals(maxans,minans)){
        return false;
    }
    return true;
}

bool NPGenerator::equals(int* g1, int* g2){
    int i;
    for(i=0;i<81;i++){
        if(g1[i]!=g2[i]){
            return false;
        }
    }
    return true;
}

bool NPGenerator::solve_min(int* board){
    int flag = check_board(board),i,k;
    int cp[81];
    if(flag == 3){
        copy_board(minans, board);
        return true;
    }else if(flag == 0){
        return false;
    }
    for(i=0;i<81;i++){
        if(board[i]&1){
            continue;
        }
        for(k=1;k<=9;k++){
            if(board[i]&(1<<k)){
                copy_board(cp, board);
                set_number(board,i,k);
                if(solve_min(board)){
                    return true;
                }else{
                    copy_board(board, cp);
                }
            }
        }
        return false;
    }
}

bool NPGenerator::solve_max(int* board){
    int flag = check_board(board),i,k;
    int cp[81];
    if(flag == 3){
        copy_board(maxans, board);
        return true;
    }else if(flag == 0){
        return false;
    }
    for(i=0;i<81;i++){
        if(board[i]&1){
            continue;
        }
        for(k=9;k>=1;k--){
            if(board[i]&(1<<k)){
                copy_board(cp, board);
                set_number(board,i,k);
                if(solve_max(board)){
                    return true;
                }else{
                    copy_board(board,cp);
                }
            }
        }
        return false;
    }
}




