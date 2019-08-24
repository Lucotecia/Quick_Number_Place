#ifndef CELLSTATE_H
#define CELLSTATE_H
#include "cell.h"
#include <QObject>

class CellState:public QObject
{
    Q_OBJECT
public:
    CellState(Cell*,QObject *parent=nullptr);
    ~CellState();

    bool isfixed();
    QString get_number();
    bool* get_memos();
    bool iscorrect();

private:
    QString number;
    bool fix_flag;
    bool correct_flag;
    bool *memos;//コンストラクタで要素数9の配列へのポインタとする
};

#endif // CELLSTATE_H

