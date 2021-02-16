#include "chess.h"
#include <QDebug>

chess::chess(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color)
{
    b = new QPushButton(w);   //創立棋子
    b->setIcon(i);
    b->setGeometry(p.x,p.y,60,60);  //設定棋子位子
    b->setIconSize(b->size());     //調整棋子大小
    b->setStyleSheet("border:none");  //去除邊框
    chessData.color = color;  //存下棋子的資料
    chessData.x = p.x;
    chessData.y = p.y;
    chessData.x1 = p.x1;
    chessData.y1 = p.y1;
    MainWindow::pos[p.x1][p.y1].ChessExist = true;  //記下該點有棋子
    MainWindow::pos[p.x1][p.y1].color = color;  //記下該點棋子顏色
    connect(v, SIGNAL(sendsignal(struct position)), this, SLOT(return_track(struct position)));  //連接滑鼠移動位置和棋子移動訊號
    connect(this, SIGNAL(sendKingData()), w, SLOT(recieveKingSignal()));  //傳送判斷是否叫出輸贏圖片的訊號

}
bool chess::judgeCanMove()  //判斷是否可移動
{
    if(MainWindow::pos[ix][jy].ChessExist==false)  //滑鼠座標上沒棋子
        return true;
    else if(MainWindow::pos[ix][jy].ChessExist==true && !MainWindow::pos[ix][jy].color==chessData.color){
        KingMightDelete();
        MainWindow::pos[ix][jy].che->~chess();  //刪除該顆棋子
        return true;  //滑鼠座標上有棋子，且滑鼠座標上的棋子顏色與點到的棋子不同
    }
    else {
        return false;
    }
}

void chess::return_track(struct position p)  //讓棋子跟滑鼠移動
{
    if(moving)
        b->setGeometry(p.x+100,p.y+80,60,60);
}

void chess::click_chess()     //讓棋子被點擊後移動
{
    if(moving == false)
        moving = true;
    else{
        moving = false;
        DefindSquarePoint();
        FindNearPoint();
        b->setGeometry(poss[ix][jy].x, poss[ix][jy].y, 60, 60);
        pointData[ix][jy].ChessExist = true;
    }
}
void chess::DefindSquarePoint(){  //存下棋盤格子點座標
    beginPoint.x = 149;
    beginPoint.y = 110;
    int dx = 61;  //兩橫線距離
    int dy = 67;  //兩直線距離
    for(int i=0; i<10; ++i){
       for(int j=0; j<9; ++j){
           poss[i][j].x = beginPoint.x+j*dy;
           poss[i][j].y = beginPoint.y+i*dx;
       }
    }
}
void chess::FindNearPoint(){
    float r = 0;    //計算滑鼠與棋盤上最接近點
    float d = 10000;
    for(int i=0; i<10;++i){
       for(int j=0; j<9;++j){
           r = (poss[i][j].x-b->geometry().x())*(poss[i][j].x-b->geometry().x())+(poss[i][j].y-b->geometry().y())*(poss[i][j].y-b->geometry().y());
           r = sqrt(r);
           if(r<d){
               d = r;
               ix = i;
               jy = j;
           }
       }
    }
}

void chess::KingMightDelete()  //判斷王是否消失
{
    if(MainWindow::pos[ix][jy].che == MainWindow::kingData[0].che){  //如果王被吃掉，刪除他的存在紀錄
        MainWindow::kingData[0].ChessExist = false;
        emit sendKingData();  //叫出判斷輸贏圖片時機的訊號
    }
    else if(MainWindow::pos[ix][jy].che == MainWindow::kingData[1].che){
        MainWindow::kingData[1].ChessExist = false;
        emit sendKingData();  //叫出判斷輸贏圖片時機的訊號
    }
}

chess::~chess(){
    delete b;
}
