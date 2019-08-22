#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cell.h"
#include "ui_cell.h"
#include <QDebug>

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
        trigger_memo(ui->memo1, 1);
        break;
    case 2:
        trigger_memo(ui->memo2, 2);
        break;
    case 3:
        trigger_memo(ui->memo3, 3);
        break;
    case 4:
        trigger_memo(ui->memo4, 4);
        break;
    case 5:
        trigger_memo(ui->memo5, 5);
        break;
    case 6:
        trigger_memo(ui->memo6, 6);
        break;
    case 7:
        trigger_memo(ui->memo7, 7);
        break;
    case 8:
        trigger_memo(ui->memo8, 8);
        break;
    case 9:
        trigger_memo(ui->memo9, 9);
        break;
    default:
        break;
    }
}

void Cell::trigger_memo(QLabel *memo, int n){
    if(memo->text()==""){
        memo->setText(QString::number(n));
        qDebug()<<n;
    }else{
        memo->setText("");
    }
}
