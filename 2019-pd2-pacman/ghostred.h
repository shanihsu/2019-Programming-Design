#ifndef GHOSTRED_H
#define GHOSTRED_H
#include "ghost.h"
#include <QKeyEvent>

class ghostRed : public ghost
{
public:
    ghostRed(QPixmap map);
    void move();
    QTimer *redGoHome;
    int MoveRuleRed(int, int, int [20][17], int);
    bool BeginMove = true;  //鬼要跑出家(移動到初始位置),true:需移動
public slots:
    void calls();  //接收到定時器的訊號時所呼叫的函式
};

#endif // GHOSTRED_H
