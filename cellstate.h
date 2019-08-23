#ifndef CELLSTATE_H
#define CELLSTATE_H
#include "cell.h"
#include <QObject>

class CellState
{

public:
    CellState(Cell*);
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

