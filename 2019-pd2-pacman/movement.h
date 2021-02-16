#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include "powerpellet.h"

//virtual function設成=0是一個pure virtual function，
//一旦一個class裡面有一個memebr function是pure virtual function，
//這個class就只能被繼承，不能被單純獨立生成

class movement : public QObject
{
    Q_OBJECT
public:
    movement();
    virtual void move() = 0;  //多型:定義鍵盤移動方向
    QGraphicsPixmapItem *p = nullptr;  //有圖片的物件
    virtual ~movement();
    int direct = 0;  //方向 上:1, 左:2, 下:3, 右:4
    int speed = 0;  //速度
    QPixmap map;  //圖片

public slots:
    virtual void calls();  //接收到定時器的訊號時所呼叫的函式
};

#endif // MOVEMENT_H
