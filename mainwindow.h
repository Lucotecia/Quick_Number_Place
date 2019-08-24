#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QTime>
#include "cell.h"
#include "displayboard.h"
#include "boardstate.h"
#include "undocontroller.h"

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
    void reflect_state(BoardState*);

signals:
    void make_board(int);
    void set_label_text(QString);
    void clear_history();
    void changed(BoardState*);
    void set_history_now(BoardState*);
    void undo();
    void redo();

public slots:
    void show_problem(QString,QString);
    void show_state(BoardState*);
    void set_enabled_undo(bool);
    void set_enabled_redo(bool);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void showTime();
    void repaint_cell();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionMemo_triggered();

    void on_actionAbout_Quick_Number_Place_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;
    //QObject **cell_array;
    QList<Cell *> all_cells;
    bool assist = true;
    Cell* selected_cell = nullptr;
    int hint = 0;
    QString correct_answer;
    //DisplayBoard *db;
    //QThread *th;
    void select(Cell*);
    Cell* find_cell(QString);
    QTimer *timer;
    QTime *time_format;
    bool memo_mode = false;
    bool compare_by_objname(Cell*,Cell*);
    BoardState* get_state();//現在の状態をBoardStateをnewして格納
    UndoController *udc;
};

#endif // MAINWINDOW_H

