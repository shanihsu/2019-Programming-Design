#ifndef PACMAN_H
#define PACMAN_H
#include "movement.h"
#include <QKeyEvent>

class pacman : public movement //繼承movement
{
public:
    pacman();
    void move();  //多型(Polymorphism):定義鍵盤移動方向
    QTimer *callMove;  //定時器,用來傳送呼叫函式的頻率
    int scores = 0;  //記分板分數
    int dotScore = 0;
    void FindNearPointMove(float, float);  //找欲移動到的點與小精靈的最接近點
    void FindNearPointNow(float, float);  //找當前座標與小精靈的最接近點
    int ix1,jy1;  //最接近點的第[ix1][jy1]點(暫存座標)
    int ix, jy;  //當前座標的第[ix][jy]點
    int PictureNum = 4;  //小精靈的圖片方向 (上:1 左:2 下:3 右:4)
    bool pelletEat = false;
public slots:
    void calls();  //接收到定時器的訊號時所呼叫的函式
};

#endif // PACMAN_H
