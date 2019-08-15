#include "cell.h"
#include "ui_cell.h"

Cell::Cell(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Cell)
{
    ui->setupUi(this);
}

Cell::~Cell()
{
    delete ui;
}
