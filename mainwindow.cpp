#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_cell.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Quick Number Place");
    all_cells = findChildren<Cell *>();
    for (int i = 0; i < all_cells.size(); i++) {
        auto cell = all_cells.at(i);
        cell->installEventFilter(this);
    }
    ui->hint_combobox->installEventFilter(this);
    installEventFilter(parent);
    db = new DisplayBoard();
    th = new QThread();
    db->moveToThread(th);
    th->start();
    connect(this,SIGNAL(make_board(int)),db,SLOT(make_board(int)));//問題作成シグナルをmainwindowからdisplayboardへ
    connect(db,SIGNAL(send_board(QString,QString)),this,SLOT(view_problem(QString, QString)));//生成された問題をmainwindowへ
    timer = new QTimer(this);
    time_format = new QTime(0,0,0);
    ui->lcdNumber->display(time_format->toString("hh:mm:ss"));
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));

    connect(ui->assist_checkbox,SIGNAL(stateChanged(int)),this,SLOT(repaint_cell()));

    //コンボボックスにfocusをあてるとキーボード入力ができるようになる
    connect(ui->assist_checkbox,SIGNAL(stateChanged(int)),ui->hint_combobox,SLOT(setFocus()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),ui->hint_combobox,SLOT(setFocus()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),ui->hint_combobox,SLOT(setFocus()));
}

MainWindow::~MainWindow()
{
    delete ui;
    th->exit();
    th->wait();
    delete timer;
    delete time_format;
}

bool MainWindow::eventKeyPress(QKeyEvent *event)
{
    auto key = event->key();
    QString target_name = "cell";
    if(key == Qt::Key_Space){
        select(ui->cell55);
        return true;
    }
    if(key == Qt::Key_Shift){
        if(memo_mode){
            memo_mode = false;
            if(ui->label->text()=="memo mode"){
                ui->label->setText("");
            }
        }else{
            memo_mode = true;
            ui->label->setText("memo mode");
        }
        return true;
    }
    if(selected_cell!=nullptr){
        int block_number = selected_cell->objectName().at(4).digitValue()-1;//0-based
        int subidx = selected_cell->objectName().at(5).digitValue()-1;//0-based
        if(key == Qt::Key_Up && !(block_number/3==0 && subidx/3==0)){//↑キーが押され選択されているcellが上端でないとき
            if(subidx/3==0){
                target_name += QString::number(block_number-3+1);
                target_name += QString::number(subidx+6+1);
            }else{
                target_name += QString::number(block_number+1);
                target_name += QString::number(subidx-3+1);
            }
            select(find_cell(target_name));
            return true;
        }else if(key == Qt::Key_Down && !(block_number/3==2 && subidx/3==2)){//↓キーが押され選択されているcellが下端でないとき
            if(subidx/3==2){
                target_name += QString::number(block_number+3+1);
                target_name += QString::number(subidx-6+1);
            }else{
                target_name += QString::number(block_number+1);
                target_name += QString::number(subidx+3+1);
            }
            select(find_cell(target_name));
            return true;
        }else if(key == Qt::Key_Left && !(block_number%3==0 && subidx%3==0)){//←キーが押され選択されているcellが左端でないとき
            if(subidx%3==0){
                target_name += QString::number(block_number-1+1);
                target_name += QString::number(subidx+2+1);
            }else{
                target_name += QString::number(block_number+1);
                target_name += QString::number(subidx-1+1);
            }
            select(find_cell(target_name));
            return true;
        }else if(key == Qt::Key_Right && !(block_number%3==2 && subidx%3==2)){//→キーが押され選択されているcellが右端でないとき
            if(subidx%3==2){
                target_name += QString::number(block_number+1+1);
                target_name += QString::number(subidx-2+1);
            }else{
                target_name += QString::number(block_number+1);
                target_name += QString::number(subidx+1+1);
            }
            select(find_cell(target_name));
            return true;
        }
        if(!(selected_cell->isfixed())){
            if(selected_cell->getText() == "" && memo_mode){
                switch (key) {
                case Qt::Key_0:
                    selected_cell->set_memo(0);
                    return true;
                case Qt::Key_1:
                    selected_cell->set_memo(1);
                    return true;
                case Qt::Key_2:
                    selected_cell->set_memo(2);
                    return true;
                case Qt::Key_3:
                    selected_cell->set_memo(3);
                    return true;
                case Qt::Key_4:
                    selected_cell->set_memo(4);
                    return true;
                case Qt::Key_5:
                    selected_cell->set_memo(5);
                    return true;
                case Qt::Key_6:
                    selected_cell->set_memo(6);
                    return true;
                case Qt::Key_7:
                    selected_cell->set_memo(7);
                    return true;
                case Qt::Key_8:
                    selected_cell->set_memo(8);
                    return true;
                case Qt::Key_9:
                    selected_cell->set_memo(9);
                    return true;
                default:
                    break;
                }
            }
            switch(key){
            case Qt::Key_0:
            case Qt::Key_Backspace:
                selected_cell->set_memo(0);
                selected_cell->setText("");
                select(selected_cell);
                return true;
            case Qt::Key_1:
                selected_cell->set_memo(0);
                selected_cell->setText("1");
                select(selected_cell);
                return true;
            case Qt::Key_2:
                selected_cell->set_memo(0);
                selected_cell->setText("2");
                select(selected_cell);
                return true;
            case Qt::Key_3:
                selected_cell->set_memo(0);
                selected_cell->setText("3");
                select(selected_cell);
                return true;
            case Qt::Key_4:
                selected_cell->set_memo(0);
                selected_cell->setText("4");
                select(selected_cell);
                return true;
            case Qt::Key_5:
                selected_cell->set_memo(0);
                selected_cell->setText("5");
                select(selected_cell);
                return true;
            case Qt::Key_6:
                selected_cell->set_memo(0);
                selected_cell->setText("6");
                select(selected_cell);
                return true;
            case Qt::Key_7:
                selected_cell->set_memo(0);
                selected_cell->setText("7");
                select(selected_cell);
                return true;
            case Qt::Key_8:
                selected_cell->set_memo(0);
                selected_cell->setText("8");
                select(selected_cell);
                return true;
            case Qt::Key_9:
                selected_cell->set_memo(0);
                selected_cell->setText("9");
                select(selected_cell);
                return true;
            default:
                return false;
            }
        }
    }
    return false;
}

bool MainWindow::eventFilter(QObject *target,QEvent *event){
    if (event->type() == QEvent::KeyPress) {
       eventKeyPress(static_cast<QKeyEvent *>(event));
       return true;
    }
    if(target->inherits("Cell")){
        if(event->type() == QEvent::MouseButtonPress){
            if(static_cast<QMouseEvent*>(event)->button()==Qt::LeftButton){
                select(static_cast<Cell*>(target));
                return true;
            }
        }
    }
    return false;
}

void MainWindow::select(Cell* target){
    for(int i=0;i<all_cells.size();i++){//全てのcellを白に
        Cell *cell = all_cells.at(i);
        cell->mark(false);
    }
    if(selected_cell!=nullptr) selected_cell->mark_frame(false);//前回選択されたcellの枠の色を戻す
    target->mark_frame(true);//選択されたcellの枠を青に
    if(ui->assist_checkbox->isChecked()){
        //checkboxがcheckされているとき、重複がないcellを全て水色に
        QChar target_block = target->objectName().at(4);
        int target_subidx = target->objectName().at(5).digitValue()-1;//0-based
        int target_block_number = target_block.digitValue()-1;//0-based
        QString target_text = static_cast<Cell *>(target)->getText();
        for(int i=0;i<all_cells.size();i++){
            Cell *cell = all_cells.at(i);
            QChar block = cell->objectName().at(4);
            int subidx = cell->objectName().at(5).digitValue()-1;//0-based
            int block_number = block.digitValue()-1;//0-based
            QString text = cell->getText();
            if(target_block==block||(target_block_number/3==block_number/3 && target_subidx/3==subidx/3)||(target_block_number%3==block_number%3 && target_subidx%3==subidx%3)){//同じブロックor同じ行or同じ列
                cell->mark(true);
            }
            if(target_text!="" && target_text==text){
                cell->mark(true, "#DDDDDD");
            }
        }
    }
    if(selected_cell!=static_cast<Cell*>(target)) selected_cell = static_cast<Cell*>(target);//selected_cellを今回選択されたcellへのポインタとする
}

void MainWindow::view_problem(QString problem, QString answer){
    correct_answer = answer;
    for(int i=0;i<all_cells.size();i++){
        Cell *cell = all_cells.at(i);
        int block_number = cell->objectName().at(4).digitValue()-1; //0-based
        int subidx = cell->objectName().at(5).digitValue()-1;       //0-based
        QString number_str = QString(problem[(block_number/3)*27+(subidx/3)*9+(block_number%3)*3+subidx%3]);
        if(number_str=="0"){
            number_str="";
            cell->fix(false);
            cell->set_font_color("blue");
        }else{
            cell->fix(true);
            cell->set_font_color("black");
        }
        cell->setText(number_str);
    }
    if(selected_cell!=nullptr) select(selected_cell);
    ui->label->setText("");
    time_format->setHMS(0,0,0);
    ui->lcdNumber->display(time_format->toString("hh:mm:ss"));
    timer->start(1000);
}

void MainWindow::on_pushButton_clicked(){
    timer->stop();
    hint = ui->hint_combobox->currentText().toInt();
    ui->label->setText("wait a minute...");
    ui->label->repaint();
    emit make_board(hint);
}

Cell* MainWindow::find_cell(QString name){
    for(int i=0;i<all_cells.length();i++){
        if(all_cells[i]->objectName()==name){
            return all_cells[i];
        }
    }
    return nullptr;
}

void MainWindow::on_pushButton_2_clicked(){
    bool flag =true;
    timer->stop();
    for(int i=0;i<all_cells.length();i++){
        Cell *cell = all_cells.at(i);
        int block_number = cell->objectName().at(4).digitValue()-1; //0-based
        int subidx = cell->objectName().at(5).digitValue()-1;       //0-based
        if(cell->getText() != QString(correct_answer[(block_number/3)*27+(subidx/3)*9+(block_number%3)*3+subidx%3])){
            flag = false;
            cell->set_font_color("red");
        }
    }
    if(flag){
        ui->label->setText("clear!");
    }else{
        ui->label->setText("wrong!");
    }
}

void MainWindow::showTime(){
    *time_format = time_format->addSecs(1);
    ui->lcdNumber->display(time_format->toString("hh:mm:ss"));
}

void MainWindow::repaint_cell(){
    if(selected_cell != nullptr){
        select(selected_cell);
    }
}
