#include "guard.h"

guard::guard(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color):chess(i, w, v, p, color)
{
    connect(b, SIGNAL(clicked()), this, SLOT(click_chess()));  //連接點擊滑鼠與棋子移動的訊號
    MainWindow::clickColor = chessData.color;  //記下滑鼠點到的棋子顏色
}

bool guard::judgeGuardRule(){
    if(MainWindow::clickColor == chessData.color)  //上一個棋子顏色跟現在相同,不可動
        return false;
    if(kingSeeKing() == true)  //如果王見王
        return false;
    if(chessData.color == true){  //棋子是黑色
        if((ix==0 || ix==1 ||ix==2)&&(jy==3 || jy==4 ||jy==5)){  //滑鼠點擊處在九宮內
            if(abs(ix-chessData.x1)==1 && abs(jy-chessData.y1)==1)  //走斜線
                return judgeCanMove();  //判斷是否可吃棋或移動
        }
    }
    else{  //棋子是紅色
        if((ix==7 || ix==8 ||ix==9)&&(jy==3 || jy==4 ||jy==5)){  //滑鼠點擊處在九宮內
            if(abs(ix-chessData.x1)==1 && abs(jy-chessData.y1)==1)  //走斜線
                return judgeCanMove();  //判斷是否可吃棋或移動
        }
    }
    return false;
}

bool guard::kingSeeKing()  //true:發生王見王, false::沒發生王見王
{
    if(MainWindow::kingData[0].ChessExist == true && MainWindow::kingData[1].ChessExist == true){  //如果兩王都存在
        int num = 0;  //兩王之間的棋子數
        if(MainWindow::kingData[0].y1 == MainWindow::kingData[1].y1){  //紅黑王在同一直線上
            for(int i=MainWindow::kingData[0].x1+1 ; i<MainWindow::kingData[1].x1 ; i++){  //計算兩王之間的棋子數
                if(MainWindow::pos[i][MainWindow::kingData[0].y1].ChessExist == true)
                    num++;
            }
        }
        if(MainWindow::kingData[0].y1 == MainWindow::kingData[1].y1
                && num == 1
                && chessData.y1 == MainWindow::kingData[0].y1
                && jy != MainWindow::kingData[0].y1)
        //紅黑王在同一直線上,且兩王之間只有一棋,且那一棋即將被移動到跟王不在同一直線上的點
            return true;
        else{
            return false;
        }
    }
    else {
        return false;
    }
}

void guard::click_chess()
{
    b->raise();  //把棋子移到最上層
    DefindSquarePoint();
    FindNearPoint();
    if(moving == false)
        moving = true;
    else if(moving == true && judgeGuardRule() == true){  //如果符合規則
        moving = false;
        DefindSquarePoint();  //定位滑鼠座標格子點
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
        b->setGeometry(poss[ix][jy].x, poss[ix][jy].y, 60, 60); //棋子移動到滑鼠位置

    }
    else {  //如果不符合規則
        moving = false;
        b->setGeometry(poss[chessData.x1][chessData.y1].x, poss[chessData.x1][chessData.y1].y, 60, 60);  //棋子不移動(回上一步)
    }
}
