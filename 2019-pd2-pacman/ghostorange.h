#ifndef GHOSTORANGE_H
#define GHOSTORANGE_H
#include "ghost.h"
#include <QKeyEvent>

class ghostOrange : public ghost
{
public:
    ghostOrange(QPixmap map);
    void move();
    QTimer *orangeGoHome;
    int MoveRuleOrange(int, int, int [20][17], int);
    int MoveRuleOrangeHome(int, int, int [20][17], int);
    void orangeRecursive();
    bool BeginMove = true;  //鬼要跑出家(移動到初始位置),true:需移動
    int directTmp = 0;
public slots:
    void calls();  //接收到定時器的訊號時所呼叫的函式
};

#endif // GHOSTORANGE_H
