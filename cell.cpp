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

void Cell::mark(bool flag){
    if(flag){
        ui->background->setStyleSheet("background-color:#CCEEFF");
    }else{
        ui->background->setStyleSheet("background-color:white");
    }
}

void Cell::select(bool flag){
    if(flag){
        ui->cellframe->setStyleSheet("border:5px solid blue");
        qDebug()<<"true";
    }else{
        qDebug()<<"false";
        ui->cellframe->setStyleSheet("border:1px solid black");
    }
}
