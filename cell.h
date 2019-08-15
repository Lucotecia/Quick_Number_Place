#ifndef CELL_H
#define CELL_H

#include <QFrame>

namespace Ui {
class Cell;
}

class Cell : public QFrame
{
    Q_OBJECT

public:
    explicit Cell(QWidget *parent = nullptr);
    ~Cell();

private:
    Ui::Cell *ui;
};

#endif // CELL_H
