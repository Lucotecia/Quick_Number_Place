#include "undocontroller.h"

UndoController::UndoController(QObject *parent):QObject(parent)
{
    now =nullptr;
}

void UndoController::undo(){
    if(!undo_stack.isEmpty()){
        redo_stack.push(now);
        now = undo_stack.pop();
        emit send_state(now);
    }
    if(undo_stack.isEmpty()) emit set_enabled_undo(false);
    emit set_enabled_redo(true);
}

void UndoController::redo(){
    if(!redo_stack.isEmpty()){
        undo_stack.push(now);
        now = redo_stack.pop();
        emit send_state(now);
    }
    if(redo_stack.isEmpty()) emit set_enabled_redo(false);
    emit set_enabled_undo(true);
}

void UndoController::changed(BoardState* bs){
    undo_stack.push(now);
    now = bs;
    clear_redo_stack();
    emit set_enabled_undo(true);
    emit set_enabled_redo(false);
}

void UndoController::clear(){
    clear_undo_stack();
    clear_redo_stack();
    delete now;
    now = nullptr;
    emit set_enabled_undo(false);
    emit set_enabled_redo(false);
}

void UndoController::set_now(BoardState* new_board){
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

