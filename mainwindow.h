#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cell.h"
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

private:
    Ui::MainWindow *ui;
    //QObject **cell_array;
    QList<Cell *> all_cells;
    bool assist = true;
    Cell* selected_cell = nullptr;
};

#endif // MAINWINDOW_H
