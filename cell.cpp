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
