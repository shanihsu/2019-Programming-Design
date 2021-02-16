#include "track_mouse.h"
#include <QDebug>
track_mouse::track_mouse(QWidget *parent) : QGraphicsView (parent)   //偵測滑鼠在棋盤上的訊號
{
    setMouseTracking(true);
}

void track_mouse::mouseMoveEvent(QMouseEvent *event)    //存下滑鼠的位置
{
    struct position p;
    p.x = event->x();
    p.y = event->y();
    emit sendsignal(p);
}
