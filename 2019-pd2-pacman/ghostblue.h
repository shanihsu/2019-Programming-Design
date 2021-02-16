#ifndef GHOSTBLUE_H
#define GHOSTBLUE_H
#include "ghost.h"
#include <QKeyEvent>

class ghostBlue : public ghost
{
public:
    ghostBlue(QPixmap map);
    void move();
    QTimer *blueGoHome;
    int vectorX = 0;
    int vectorY = 0;
    void vectorPoint();
    int MoveRuleBlue(int, int, int [20][17], int);
    bool BeginMove = true;  //鬼要跑出家(移動到初始位置),true:需移動
public slots:
    void calls();  //接收到定時器的訊號時所呼叫的函式
};

#endif // GHOSTBLUE_H
