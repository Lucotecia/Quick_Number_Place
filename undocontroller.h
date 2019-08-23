#ifndef UNDOCONTROLLER_H
#define UNDOCONTROLLER_H
#include <QObject>
#include <QStack>
#include "boardstate.h"


class UndoController
{
public:
    UndoController();
    BoardState* undo();
    BoardState* redo();
    void changed(BoardState*);
    void clear();
    void set_history_now(BoardState*);
    bool is_empty_undo();
    bool is_empty_redo();

private:
    void clear_undo_stack();
    void clear_redo_stack();
    QStack<BoardState*> undo_stack, redo_stack;
    BoardState* now;
};

#endif // UNDOCONTROLLER_H
