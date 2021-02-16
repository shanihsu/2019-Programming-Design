#include "king.h"
#include <QDebug>
king::king(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color):chess(i, w, v, p, color)
{
    connect(b, SIGNAL(clicked()), this, SLOT(click_chess()));  //連接點擊滑鼠與棋子移動的訊號
    MainWindow::clickColor = chessData.color;  //記下滑鼠點到的棋子顏色
    int a; //轉換bool跟int
    if(chessData.color == true)
        a = 0;
    else {
        a = 1;
    }
    MainWindow::kingData[a].x = p.x;  //存下王的座標資料
    MainWindow::kingData[a].y = p.y;
    MainWindow::kingData[a].x1 = p.x1;
    MainWindow::kingData[a].y1 = p.y1;
    MainWindow::kingData[a].ChessExist = true;
    MainWindow::kingData[a].che = this;
}

bool king::judgeKingRule(){
    if(MainWindow::clickColor == chessData.color)  //上一個棋子顏色跟現在相同,不可動
        return false;
    if(kingSeeKing() == true)  //如果王見王
        return false;
    if(chessData.color == true){   //棋子是黑色
        if((ix==0 || ix==1 ||ix==2)&&(jy==3 || jy==4 ||jy==5)){  //滑鼠點擊處在九宮內
            if(((ix==chessData.x1) && abs(jy-chessData.y1)==1) || ((jy==chessData.y1) && abs(ix-chessData.x1)==1)){  //走一步
                return judgeCanMove();  //判斷是否可吃棋或移動
            }
        }
    }
    else{   //棋子是紅色
        if((ix==7 || ix==8 ||ix==9)&&(jy==3 || jy==4 ||jy==5)){  //滑鼠點擊處在九宮內
            if((ix==chessData.x1 && abs(jy-chessData.y1)==1) || (jy==chessData.y1 && abs(ix-chessData.x1)==1)){   //走一步
                return judgeCanMove();  //判斷是否可吃棋或移動
            }
        }
    }
    return false;
}

bool king::kingSeeKing()  //true:發生王見王, false::沒發生王見王
{
    if(MainWindow::kingData[0].ChessExist == true && MainWindow::kingData[1].ChessExist == true){  //如果兩王都存在
        int a;  //轉換bool跟int,不同色的棋子相反存
        if(!chessData.color == true)
            a = 0;
        else {
            a = 1;
        }
        int num = 0;
        if(jy == MainWindow::kingData[a].y1){  //若要移動到的那直線上有另一個王
            if(MainWindow::kingData[a].x1 < ix){  //移動紅帥
                for(int i=MainWindow::kingData[a].x1+1 ; i<ix ; i++){  //計算兩王之間的棋子數
                    if(MainWindow::pos[i][jy].ChessExist == true)
                        num++;
                }
            }
            else{  //移動黑將
                for(int i=ix+1 ; i<MainWindow::kingData[a].x1 ; i++){  //計算兩王之間的棋子數
                    if(MainWindow::pos[i][jy].ChessExist == true)
                        num++;
                }
            }
        }
        if(jy == MainWindow::kingData[a].y1 && num == 0)  //如果王要移動到的那一條直線上有另一個王,且兩王之間沒有棋子
            return true;
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void king::click_chess()
{
    b->raise();  //把棋子移到最上層
    DefindSquarePoint();
    FindNearPoint();  //定位滑鼠座標格子點
    if(moving == false)
        moving = true;
    else if(moving == true && judgeKingRule() == true){  //如果符合規則
        moving = false;
        DefindSquarePoint();
        FindNearPoint();
        MainWindow::clickColor = chessData.color;  //記下滑鼠點到的棋子顏色
        MainWindow::pos[chessData.x1][chessData.y1].ChessExist = false;  //消去該點有棋子的紀錄
        MainWindow::pos[chessData.x1][chessData.y1].color = false;  //消去該點棋子的顏色
        MainWindow::pos[chessData.x1][chessData.y1].che = nullptr;  //消去該點的棋子
        chessData.x = poss[ix][jy].x;  //棋子的座標換成滑鼠的座標
        chessData.y = poss[ix][jy].y;
        chessData.x1 = ix;
        chessData.y1 = jy;
        MainWindow::pos[ix][jy].ChessExist = true;  //記下該點有棋子
        MainWindow::pos[ix][jy].color = chessData.color;  //記下該點棋子的顏色
        MainWindow::pos[ix][jy].che = this;  //記下該點的棋子
        int a;  //轉換bool跟int
        if(chessData.color == true)
            a = 0;
        else {
            a = 1;
        }
        MainWindow::kingData[a].x1 = ix;//更改王的座標資料
        MainWindow::kingData[a].y1 = jy;
        b->setGeometry(poss[ix][jy].x, poss[ix][jy].y, 60, 60); //棋子移動到滑鼠位置

    }
    else {  //如果不符合規則
        moving = false;
        b->setGeometry(poss[chessData.x1][chessData.y1].x, poss[chessData.x1][chessData.y1].y, 60, 60);  //棋子不移動(回上一步)
    }
}
