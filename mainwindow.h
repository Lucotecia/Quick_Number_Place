#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "cell.h"
#include "displayboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject*,QEvent*);
    bool eventKeyPress(QKeyEvent*);

signals:
    void make_board(int);
    void set_label_text(QString);

public slots:
    void view_problem(QString,QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //QObject **cell_array;
    QList<Cell *> all_cells;
    bool assist = true;
    Cell* selected_cell = nullptr;
    int hint = 0;
    QString correct_answer;
    DisplayBoard *db;
    QThread *th;

    void select(Cell*);
    Cell* find_cell(QString);

};

#endif // MAINWINDOW_H
