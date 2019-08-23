#ifndef CELL_H
#define CELL_H

#include <QFrame>
#include <QMouseEvent>
#include <QLabel>

namespace Ui {
class Cell;
}

class Cell : public QFrame
{
    Q_OBJECT

public:
    explicit Cell(QWidget *parent = nullptr);
    ~Cell();
    void mark(bool,QString color_name = "#CCEEFF");
    void mark_frame(bool);
    void setText(QString);
    void fix(bool);
    QString getText();
    bool isfixed();
    void set_font_color(QString);
    void set_correct(bool);
    void set_memo(int);
    void get_memos(bool*);//要素数9以上の空の配列を渡すこと
    bool iscorrect();
    void set_memos(bool*);//undo/redo用

private:
    Ui::Cell *ui;
    bool fix_flag = false;
    QList<QLabel*> labels;
    static void switch_memo(QLabel*,int);
    bool correct = true;
};

#endif // CELL_H
