#include "boardstate.h"

BoardState::~BoardState(){
    int size = state.size();
    while(size>0){
        delete state.at(size-1);
        size--;
    }
}

void BoardState::push_back(CellState* cs){
    state.push_back(cs);
}

CellState* BoardState::at(int idx){
    return state.at(idx);
}
