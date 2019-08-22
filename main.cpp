﻿#include "mainwindow.h"
#include <QApplication>
#include "displayboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon.ico"));
    MainWindow w;
    w.show();

    return a.exec();
}
