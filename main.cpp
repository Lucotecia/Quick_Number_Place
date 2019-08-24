#include "mainwindow.h"
#include "displayboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon.ico"));
    MainWindow w;

    DisplayBoard *db = new DisplayBoard();
    QThread *th = new QThread();
    db->moveToThread(th);
    th->start();
    QObject::connect(&w, SIGNAL(make_board(int)), db, SLOT(make_board(int)));//問題作成シグナルをmainwindowからdisplayboardへ
    QObject::connect(db, SIGNAL(send_board(QString, QString)), &w, SLOT(show_problem(QString, QString)));//生成された問題をmainwindowへ
    w.show();
    int ret = a.exec();
    delete db;
    th->exit();
    th->wait();
    delete th;
    return ret;
}


