#include "pown.h"

pown::pown(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color):chess(i, w, v, p, color)
{
    connect(b, SIGNAL(clicked()), this, SLOT(click_chess()));  //連接點擊滑鼠與棋子移動的訊號
    MainWindow::clickColor = chessData.color;  //記下滑鼠點到的棋子顏色
    connect(this, SIGNAL(sendKingData()), w, SLOT(recieveKingSignal()));  //傳送判斷是否叫出輸贏圖片的訊號
}

bool pown::judgePownRule(){
    if(MainWindow::clickColor == chessData.color)  //上一個棋子顏色跟現在相同,不可動
        return false;
    int chessnum = 0;  //滑鼠座標與棋子座標間的棋子數(不包含滑鼠座標，不包含棋子座標)
    if(ix != chessData.x1 &&jy != chessData.y1) //如果滑鼠座標不在棋子所在之十字上
        return false;
    if(kingSeeKing() == true)  //如果王見王
        return false;
    if(jy < chessData.y1){  //左
        for(int i=jy+1; i<chessData.y1; ++i){  //滑鼠座標與棋子座標之間(不包含滑鼠座標，不包含棋子座標)
            if(MainWindow::pos[ix][i].ChessExist == true)  //有棋子
                chessnum++;
        }
        if(chessnum==0 && MainWindow::pos[ix][jy].ChessExist == false)  //滑鼠座標與棋子座標間沒棋子
            return true;
        else if(chessnum==1 && MainWindow::pos[ix][jy].ChessExist==true && !MainWindow::pos[ix][jy].color==chessData.color){
            KingMightDelete();  //判斷王是否消失
            MainWindow::pos[ix][jy].che->~chess();  //刪除該顆棋子
            return true;
        }
        //滑鼠座標與棋子座標間有一個棋子，且滑鼠座標上有棋子，且滑鼠座標上的棋子顏色與點到的棋子不同
    }
    else if (jy >chessData.y1){  //右
        for(int i=chessData.y1+1; i<jy; ++i){  //滑鼠座標與棋子座標之間(不包含滑鼠座標，不包含棋子座標)
            if(MainWindow::pos[ix][i].ChessExist == true)  //有棋子
                chessnum++;
        }
        if(chessnum==0 && MainWindow::pos[ix][jy].ChessExist == false)  //滑鼠座標與棋子座標間沒棋子
            return true;
        else if(chessnum==1 && MainWindow::pos[ix][jy].ChessExist==true && !MainWindow::pos[ix][jy].color==chessData.color){
            KingMightDelete();  //判斷王是否消失
            MainWindow::pos[ix][jy].che->~chess();  //刪除該顆棋子
            return true;
            }
        //滑鼠座標與棋子座標間有一個棋子，且滑鼠座標上有棋子，且滑鼠座標上的棋子顏色與點到的棋子不同
    }
    if(ix < chessData.x1){  //上
        for(int i=ix+1; i<chessData.x1; ++i){  //滑鼠座標與棋子座標之間(不包含滑鼠座標，不包含棋子座標)
            if(MainWindow::pos[i][jy].ChessExist == true)  //有棋子
                chessnum++;
        }
        if(chessnum==0 && MainWindow::pos[ix][jy].ChessExist == false)  //滑鼠座標與棋子座標間沒棋子
            return true;
        else if(chessnum==1 && MainWindow::pos[ix][jy].ChessExist==true && !MainWindow::pos[ix][jy].color==chessData.color){
            KingMightDelete();  //判斷王是否消失
            MainWindow::pos[ix][jy].che->~chess();  //刪除該顆棋子
            return true;
        }
        //滑鼠座標與棋子座標間有一個棋子，且滑鼠座標上有棋子，且滑鼠座標上的棋子顏色與點到的棋子不同
    }
    else if(ix > chessData.x1){  //下
        for(int i=chessData.x1+1; i<ix; ++i){  //滑鼠座標與棋子座標之間(不包含滑鼠座標，不包含棋子座標)
            if(MainWindow::pos[i][jy].ChessExist == true)  //有棋子
                chessnum++;
        }
        if(chessnum==0 && MainWindow::pos[ix][jy].ChessExist == false)  //滑鼠座標與棋子座標間沒棋子
            return true;
        else if(chessnum==1 && MainWindow::pos[ix][jy].ChessExist==true && !MainWindow::pos[ix][jy].color==chessData.color){
            KingMightDelete();  //判斷王是否消失
            MainWindow::pos[ix][jy].che->~chess();  //刪除該顆棋子
            return true;
        }
        //滑鼠座標與棋子座標間有一個棋子，且滑鼠座標上有棋子，且滑鼠座標上的棋子顏色與點到的棋子不同
    }
    return false;
}

bool pown::kingSeeKing()  //true:發生王見王, false::沒發生王見王
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

void pown::click_chess()
{
    b->raise();  //把棋子移到最上層
    DefindSquarePoint();
    FindNearPoint();  //定位滑鼠座標最接近的格子點
    if(moving == false)
        moving = true;
    else if(moving == true && judgePownRule() == true){  //如果符合規則
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
        b->setGeometry(poss[ix][jy].x, poss[ix][jy].y, 60, 60); //棋子移動到滑鼠位置
    }
    else {  //如果不符合規則
        moving = false;
        b->setGeometry(poss[chessData.x1][chessData.y1].x, poss[chessData.x1][chessData.y1].y, 60, 60);  //棋子不移動(回上一步)
    }
}
