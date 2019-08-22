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
    void set_memo(int);

private:
    Ui::Cell *ui;
    bool fix_flag = true;
    QList<QLabel*> labels;
    static void trigger_memo(QLabel*,int);
};

#endif // CELL_H
