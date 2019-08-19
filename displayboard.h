#ifndef DISPLAYBOARD_H
#define DISPLAYBOARD_H
#include "npgenerator.h"
#include <QObject>
#include <QEvent>
#include <QThread>

class DisplayBoard : public QObject//後でNPGeneratorをマルチスレッド化するためのクラス
{
    Q_OBJECT
public:
    explicit DisplayBoard(QObject *parent=nullptr);

signals:
    void send_board(QString,QString);
public slots:
    void make_board(int);

private:
    QString problem, answer;
};

#endif // DISPLAYBOARD_H
