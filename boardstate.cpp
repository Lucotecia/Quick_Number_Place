#include "boardstate.h"

BoardState::BoardState(QObject *parent):QObject(parent)
{}

BoardState::~BoardState(){
    int i = state.size();
    while(i>0){
        i--;
        delete state.at(i);
    }
}

void BoardState::push_back(CellState* cs){
    state.push_back(cs);
}

CellState* BoardState::at(int idx){
    return state.at(idx);
}
