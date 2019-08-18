#include "mainwindow.h"
#include <QApplication>
#include "displayboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DisplayBoard db;
    QObject::connect(&w,SIGNAL(make_board(int)),&db,SLOT(make_board(int)));//問題作成シグナルをmainwindowからdisplayboardへ
    QObject::connect(&db,SIGNAL(send_board(QString,QString)),&w,SLOT(view_problem(QString, QString)));//生成された問題をmainwindowへ
    w.show();

    return a.exec();
}
