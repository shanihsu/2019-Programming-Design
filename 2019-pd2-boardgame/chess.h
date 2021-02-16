#ifndef CHESS_H
#define CHESS_H
#include <QPushButton>
#include <QObject>
#include "mainwindow.h"
#include <QGraphicsView>
#include "math.h"

class chess : public QObject
{
    Q_OBJECT
public:
    QPushButton *b;
    chess(QIcon, MainWindow *, QGraphicsView *, struct position, bool);
    virtual ~chess();
    bool moving = false;
    bool color ;
    bool judgeCanMove();  //判斷是否可移動
    struct position beginPoint;  //poss[0][0]的點座標
    struct position poss[10][9];  //格子點座標
    struct position pointData[10][9];  ////棋子資料
    struct position chessData;  //棋子資料
    int ix;  //滑鼠最接近的格子點第[ix][jy]點
    int jy;
    void DefindSquarePoint();   //存下格子點座標
    void FindNearPoint();   //找到距離最接近的點

public slots:
    void return_track(struct position);
    virtual void click_chess();  //點擊棋子後會發生的事
    void KingMightDelete();  //判斷王是否消失
signals:
    void sendKingData();  //叫出判斷輸贏圖片時機的訊號
};

#endif // CHESS_H
