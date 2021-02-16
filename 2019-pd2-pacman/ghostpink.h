#ifndef GHOSTPINK_H
#define GHOSTPINK_H
#include "ghost.h"
#include <QKeyEvent>


class ghostPink :public ghost
{
public:
    ghostPink(QPixmap map);
    void move();
    QTimer *pinkGoHome;
    int MoveRulePink(int, int, int [20][17], int);
    bool BeginMove = true;  //鬼要跑出家(移動到初始位置),true:需移動
public slots:
    void calls();  //接收到定時器的訊號時所呼叫的函式
};

#endif // GHOSTPINK_H
