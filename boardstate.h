#ifndef BOARDSTATE_H
#define BOARDSTATE_H
#include <QObject>
#include "cellstate.h"
#include <QVector>
class BoardState:public QObject
{
    Q_OBJECT
public:
    BoardState(QObject *parent=nullptr);
    ~BoardState();

    void push_back(CellState*);
    CellState* at(int);
private:
    QVector<CellState*> state;//要素数81
};

#endif // BOARDSTATE_H
