#include "cellstate.h"

CellState::CellState(Cell*cell,QObject *parent):QObject(parent)
{
    memos = new bool[9];
    number = cell->getText();
    fix_flag = cell->isfixed();
    cell->get_memos(memos);
    correct_flag = cell->iscorrect();
}

CellState::~CellState(){
    delete [] memos;
}

bool CellState::isfixed(){
    return fix_flag;
}

QString CellState::get_number(){
    return number;
}

bool* CellState::get_memos(){
    return memos;
}

bool CellState::iscorrect(){
    return correct_flag;
}
