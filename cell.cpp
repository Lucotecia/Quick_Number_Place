#include "cell.h"
#include "ui_cell.h"

Cell::Cell(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Cell)
{
    ui->setupUi(this);
    labels = findChildren<QLabel*>();
}

Cell::~Cell()
{
    delete ui;
}

void Cell::mark(bool flag, QString color_name){
    if(flag){
        ui->background->setStyleSheet("background-color:"+color_name);
    }else{
        ui->background->setStyleSheet("background-color:white");
    }
}

void Cell::mark_frame(bool flag){
    if(flag){
        ui->cellframe->setStyleSheet("border:5px solid blue");
    }else{
        ui->cellframe->setStyleSheet("border:1px solid black");
    }
}

void Cell::setText(QString s){
    ui->label->setText(s);
}

void Cell::fix(bool flag){//true:固定・黒文字, false:入力可能・青文字
    fix_flag = flag;
}

void Cell::set_font_color(QString color){
    ui->label->setStyleSheet("color:"+color);
}

QString Cell::getText(){
    return ui->label->text();
}

bool Cell::isfixed(){
    return fix_flag;
}

void Cell::set_memo(int n){
    if(n==0){
        for(int i=0;i<labels.length();i++){
            labels[i]->setText("");
        }
    }
    switch(n){
    case 1:
        switch_memo(ui->memo1, 1);
        break;
    case 2:
        switch_memo(ui->memo2, 2);
        break;
    case 3:
        switch_memo(ui->memo3, 3);
        break;
    case 4:
        switch_memo(ui->memo4, 4);
        break;
    case 5:
        switch_memo(ui->memo5, 5);
        break;
    case 6:
        switch_memo(ui->memo6, 6);
        break;
    case 7:
        switch_memo(ui->memo7, 7);
        break;
    case 8:
        switch_memo(ui->memo8, 8);
        break;
    case 9:
        switch_memo(ui->memo9, 9);
        break;
    default:
        break;
    }
}

void Cell::switch_memo(QLabel *memo, int n){
    if(memo->text()==""){
        memo->setText(QString::number(n));
    }else{
        memo->setText("");
    }
}

void Cell::get_memos(bool* copy){
    copy[0] = ui->memo1->text()!="";
    copy[1] = ui->memo2->text()!="";
    copy[2] = ui->memo3->text()!="";
    copy[3] = ui->memo4->text()!="";
    copy[4] = ui->memo5->text()!="";
    copy[5] = ui->memo6->text()!="";
    copy[6] = ui->memo7->text()!="";
    copy[7] = ui->memo8->text()!="";
    copy[8] = ui->memo9->text()!="";
}

void Cell::set_correct(bool c){
    correct = c;
}

bool Cell::iscorrect(){
    return correct;
}

void Cell::set_memos(bool *arr){
    arr[0]?ui->memo1->setText("1"):ui->memo1->setText("");
    arr[1]?ui->memo2->setText("2"):ui->memo2->setText("");
    arr[2]?ui->memo3->setText("3"):ui->memo3->setText("");
    arr[3]?ui->memo4->setText("4"):ui->memo4->setText("");
    arr[4]?ui->memo5->setText("5"):ui->memo5->setText("");
    arr[5]?ui->memo6->setText("6"):ui->memo6->setText("");
    arr[6]?ui->memo7->setText("7"):ui->memo7->setText("");
    arr[7]?ui->memo8->setText("8"):ui->memo8->setText("");
    arr[8]?ui->memo9->setText("9"):ui->memo9->setText("");
}
