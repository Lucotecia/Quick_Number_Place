#include "displayboard.h"

DisplayBoard::DisplayBoard(QObject *parent) :
    QObject(parent)
{}

void DisplayBoard::make_board(int hint){
    NPGenerator *npg = new NPGenerator(hint);
    npg->generate();
    problem = npg->get_problem();
    answer = npg->get_answer();
    emit send_board(problem, answer);
}
