#ifndef NPGENERATOR_H
#define NPGENERATOR_H

#include <QObject>
#include <random>
#include <ctime>
#include <QString>

class NPGenerator : public QObject
{
    Q_OBJECT
public:
    explicit NPGenerator(int,QObject *parent = nullptr);
    ~NPGenerator();
    void generate();
    QString get_problem();
    QString get_answer();

signals:

public slots:


private:
   int problem[81], answer[81], minans[81], maxans[81];
   int rest;
   static std::mt19937 *seed;
   std::mt19937 *engine_ptr;

   void init_board(int*);
   void copy_board(int*, int*);
   void eliminate(int*, const int, const int);
   int check_board(int*);
   int get_number(int*, const int);
   bool fill_answer();
   void set_number(int*, const int, const int);
   bool hole();
   bool issolvable();
   bool equals(int*, int*);
   bool solve_min(int*);
   bool solve_max(int*);
};

#endif // NPGENERATOR_H
