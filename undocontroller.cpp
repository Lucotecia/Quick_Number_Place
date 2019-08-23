#include "undocontroller.h"

UndoController::UndoController(){
    now =nullptr;
}

BoardState* UndoController::undo(){
    if(undo_stack.isEmpty()){
        return nullptr;
    }
    redo_stack.push(now);
    now = undo_stack.pop();
    return now;
}

BoardState* UndoController::redo(){
    if(redo_stack.isEmpty()){
        return nullptr;
    }
    undo_stack.push(now);
    now = redo_stack.pop();
    return now;
}

void UndoController::changed(BoardState* bs){
    undo_stack.push(now);
    now = bs;
    clear_redo_stack();
}

void UndoController::clear(){
    clear_undo_stack();
    clear_redo_stack();
    delete now;
    now = nullptr;
}

void UndoController::set_history_now(BoardState* new_board){
    now = new_board;
}

void UndoController::clear_undo_stack(){
    while(!undo_stack.isEmpty()){
        delete undo_stack.pop();
    }
}

void UndoController::clear_redo_stack(){
    while(!redo_stack.isEmpty()){
        delete redo_stack.pop();
    }
}

bool UndoController::is_empty_undo(){
    return undo_stack.isEmpty();
}

bool UndoController::is_empty_redo(){
    return redo_stack.isEmpty();
}
