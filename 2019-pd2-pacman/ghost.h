#ifndef GHOST_H
#define GHOST_H
#include "movement.h"
#include <QKeyEvent>

class ghost : public movement //繼承movement
{
public:
    ghost();
    void move();
    QTimer *callMove;  //定時器,用來傳送呼叫函式的頻率
    QTimer *timePellet;
    void FindNearPointMove(float, float);  //找欲移動到的點與小精靈的最接近點
    void FindNearPointNow(float, float);  //找當前座標與小精靈的最接近點
    int WallTmp[20][17];  //可更動的地圖(移動後須把原本位置設成牆壁，不可走重複路徑(最段路徑))
    int ix1,jy1;  //最接近點的第[ix1][jy1]點(暫存座標)
    int ix, jy;  //當前座標的第[ix][jy]點
public slots:
    void calls();  //接收到定時器的訊號時所呼叫的函式
};

#endif // GHOST_H
