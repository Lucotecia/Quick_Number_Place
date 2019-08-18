﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_cell.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    int block_r,block_c,cell_r,cell_c;
    ui->setupUi(this);
//    for(block_r=0;block_r<3;block_r++){
//        for(block_c=0;block_c<3;block_c++){
//            for(cell_r=0;cell_r<3;cell_r++){
//                for(cell_c=0;cell_c<3;cell_c++){
//                    cell_array[block_r*27+block_c*3+cell_r*9+cell_c] = ui->gridLayout->itemAtPosition(3*block_r+cell_r, 3*block_c+cell_c)->widget();
//                }
//            }
//        }
//    }
//    dynamic_cast<Cell*>(cell_array[30])->select(false);
    all_cells = findChildren<Cell *>();
    for (int i = 0; i < all_cells.size(); i++) {
        auto cell = all_cells.at(i);
        qDebug()<<cell->objectName();
        cell->installEventFilter(this);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *target,QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        if(static_cast<QMouseEvent*>(event)->button()==Qt::LeftButton){
            if(target->inherits("Cell")){
                for(int i=0;i<all_cells.size();i++){//全てのcellを白に
                    auto cell = all_cells.at(i);
                    static_cast<Cell*>(cell)->mark(false);
                }
                if(selected_cell!=nullptr) selected_cell->select(false);//前回選択されたcellの枠の色を戻す
                static_cast<Cell *>(target)->select(true);//選択されたcellの枠を青に
                static_cast<Cell *>(target)->mark(true);//選択されたcellを水色に
                if(assist){
                    //assistがtrueのとき、重複がないcellを全て水色に
                    QChar target_block = target->objectName().at(4);
                    int target_subidx = target->objectName().at(5).digitValue()-1;//0-based
                    int target_block_number = target_block.digitValue()-1;//0-based
                    QString target_text = static_cast<Cell *>(target)->getText();
                    for(int i=0;i<all_cells.size();i++){
                        Cell *cell = all_cells.at(i);
                        QChar block = cell->objectName().at(4);
                        int subidx = cell->objectName().at(5).digitValue()-1;//0-based
                        int blocknumber = block.digitValue()-1;//0-based
                        QString text = cell->getText();
                        if(target_block==block||(target_block_number/3==blocknumber/3 && target_subidx/3==subidx/3)||(target_block_number%3==blocknumber%3 && target_subidx%3==subidx%3)){//同じブロックor同じ行or同じ列
                            cell->mark(true);
                        }
                        if(target_text!="" && target_text==text){
                            cell->mark(true, "#DDDDDD");
                        }
                    }
                }
                selected_cell = static_cast<Cell*>(target);//selected_cellを今回選択されたcellへのポインタとする
                qDebug() << target->objectName();
            }
        }
    }
    return false;
}

void MainWindow::view_problem(QString problem, QString answer){
    correct_answer = answer;
    qDebug() << problem;
    qDebug() << answer;
    for(int i=0;i<all_cells.size();i++){
        Cell *cell = all_cells.at(i);
        int block_number = cell->objectName().at(4).digitValue()-1;//0-based
        int subidx = cell->objectName().at(5).digitValue()-1;//0-based
        QString number_str = QString(problem[(block_number/3)*27+(subidx/3)*9+(block_number%3)*3+subidx%3]);
        if(number_str=="0"){
            number_str="";
            cell->fix(false);
        }else{
            cell->fix(true);
        }
        cell->setText(number_str);
    }
}

void MainWindow::on_pushButton_clicked()
{
    hint = ui->hint_combobox->currentText().toInt();
    emit make_board(hint);
}
