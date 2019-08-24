#ifndef UNDOCONTROLLER_H
#define UNDOCONTROLLER_H
#include <QObject>
#include <QStack>
#include "boardstate.h"


class UndoController:public QObject
{
    Q_OBJECT
public:
    UndoController(QObject *parent=nullptr);

signals:
    void send_state(BoardState*);
    void set_enabled_undo(bool);
    void set_enabled_redo(bool);

public slots:
    void clear();
    void changed(BoardState*);
    void set_now(BoardState*);
    void undo();
    void redo();

private:
    void clear_undo_stack();
    void clear_redo_stack();
    QStack<BoardState*> undo_stack, redo_stack;
    BoardState* now;
};

#endif // UNDOCONTROLLER_H
