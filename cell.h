#ifndef CELL_H
#define CELL_H

#include <QFrame>
#include <QMouseEvent>

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
    void select(bool);
    void setText(QString);
    void fix(bool);
    QString getText();

private:
    Ui::Cell *ui;
    bool isfixed = false;
};

#endif // CELL_H
