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
    void mark(bool);
    void select(bool);

private:
    Ui::Cell *ui;
};

#endif // CELL_H
