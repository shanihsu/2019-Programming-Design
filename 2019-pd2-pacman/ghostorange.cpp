#include "ghostorange.h"
#include <mainwindow.h>
#include <QDebug>

ghostOrange::ghostOrange(QPixmap map)
{
    p = new QGraphicsPixmapItem(map);  //設定鬼物件
    p->setScale(0.085);  //設定鬼大小
    p->setPos(MainWindow::pos[8][7].x, MainWindow::pos[8][7].y+10);  //設定小精靈初始位置
    ix = 8;  //記下當前鬼的格子點
    jy = 7;
    p->setOffset(-map.width()/2, -map.height()/2);  //將鬼的中心點對準點點
    orangeGoHome = new QTimer();
    connect(orangeGoHome, &QTimer::timeout, [=](){
        qDebug()<<"111111";
        p->show();
        BeginMove = true;
        direct = 4;
        orangeGoHome->stop();
    });
}

void ghostOrange::move()  //定義鍵盤移動方向
{
    if(BeginMove == true){  //如果鬼還沒移出家
        FindNearPointMove(p->pos().x(), p->pos().y()-speed);  //找欲移動的位置與點點最接近的點
        if(p->pos().y()-speed < MainWindow::pos[7][7].y){  //欲移動位置超出(跑出初始位置的點)
            p->setY(MainWindow::pos[7][7].y);  //停在初始位置
            ix = 7;  //存下當前座標格子點
            jy = 7;
        }
        else{
            p->setY(p->pos().y() - speed);  //移動
            FindNearPointNow(p->pos().x(), p->pos().y() - speed);   //存下當前座標格子點
        }
        if(p->pos().y() == MainWindow::pos[7][7].y){  //如果鬼已經在初始位置
            BeginMove = false;  //不須再移動
        }
    }
    else{  //如果鬼已經移出家
           if(direct == 1){  //上
                FindNearPointMove(p->pos().x(), p->pos().y()-speed);  //找欲移動的位置與點點最接近的點
                if(MainWindow::pos[ix1][jy1].CanMove == true){  //如果最接近點(欲移動的位置)沒有障礙物
                    if(p->pos().y()-speed < MainWindow::pos[0][jy1].y){  //如果欲移動的位置超出邊界
                          p->setY(MainWindow::pos[ix1][jy1].y);  //停在邊界前
                          ix = ix1;  //存下當前座標格子點
                          jy = jy1;
                          orangeRecursive();
                    }
                    else if(MainWindow::pos[ix1-1][jy1].CanMove == false && p->pos().y()-speed < MainWindow::pos[ix1][jy1].y){  //如果欲移動到的點有牆壁
                        p->setY(MainWindow::pos[ix1][jy1].y);  //停在牆壁前
                        ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else if(MainWindow::DotExist[ix1][jy1] == 2 && p->pos().y()-speed < MainWindow::pos[ix1][jy1].y){  //如果遇到轉彎
                        p->setY(p->pos().y() - speed);  //移動
                        ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else{
                        p->setY(p->pos().y() - speed);  //移動
                        FindNearPointNow(p->pos().x(), p->pos().y()-speed);  //存下當前座標格子點
                    }
                }
            }
            else if(direct ==2){  //左
                float tmpX;
                float tmpY;
                FindNearPointMove(p->pos().x()-speed, p->pos().y());  //找欲移動的位置與點點最接近的點
                if(MainWindow::DotExist[ix1][jy1] == 2){
                    tmpX = MainWindow::pos[ix1][jy1].x;
                    tmpY = MainWindow::pos[ix1][jy1].y;
                }
                if(MainWindow::pos[ix1][jy1].CanMove == true){  //如果最接近點(欲移動的位置)沒有障礙物
                    if(p->pos().x()-speed <MainWindow::pos[ix1][0].x){  //如果欲移動的位置超出邊界
                        if(ix1 == 9){  //如果在互通的地方
                            p->setX(p->pos().x() - speed);
                            FindNearPointNow(p->pos().x()-speed, p->pos().y());  //存下當前座標格子點
                            p->setX(MainWindow::pos[9][16].x - speed);  //從另一邊進來
                            FindNearPointNow(MainWindow::pos[9][16].x - speed, p->pos().y());  //存下當前座標格子點
                        }
                        else{
                            p->setX(MainWindow::pos[ix1][jy1].x);  //停在邊界前
                            ix = ix1;  //存下當前座標格子點
                            jy = jy1;
                            orangeRecursive();
                        }
                    }
                    else if(MainWindow::pos[ix1][jy1-1].CanMove == false && p->pos().x()-speed < MainWindow::pos[ix1][jy1].x){  //如果欲移動到的點有牆壁
                        p->setX(MainWindow::pos[ix1][jy1].x);  //停在牆壁前
                        ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else if(MainWindow::DotExist[ix1][jy1] == 2 && p->pos().x()-speed < MainWindow::pos[ix1][jy1].x){
                        p->setX(p->pos().x() - speed);  //移動                    ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else{
                        p->setX(p->pos().x() - speed);  //移動
                        FindNearPointNow(p->pos().x()-speed, p->pos().y());  //存下當前座標格子點
                    }
                }
            }
            else if(direct == 3){  //下
                float tmpX;
                float tmpY;
                FindNearPointMove(p->pos().x(), p->pos().y()+speed);  //找欲移動的位置與點點最接近的點
                if(MainWindow::DotExist[ix1][jy1] == 2){
                    tmpX = MainWindow::pos[ix1][jy1].x;
                    tmpY = MainWindow::pos[ix1][jy1].y;
                }
                if(MainWindow::pos[ix1][jy1].CanMove == true){  //如果最接近點(欲移動的位置)沒有障礙物
                    if(p->pos().y()+speed > MainWindow::pos[19][jy1].y){  //如果欲移動的位置超出邊界
                        p->setY(MainWindow::pos[ix1][jy1].y);  //停在邊界前
                        ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else if(MainWindow::pos[ix1+1][jy1].CanMove == false && p->pos().y()+speed > MainWindow::pos[ix1][jy1].y){  //如果欲移動到的點有牆壁
                        p->setY(MainWindow::pos[ix1][jy1].y);  //停在牆壁前
                        ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else if(MainWindow::DotExist[ix1][jy1] == 2 && p->pos().y()+speed > MainWindow::pos[ix1][jy1].y){
                        p->setY(p->pos().y() + speed);  //移動
                        ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else{
                        p->setY(p->pos().y() + speed);  //移動
                        FindNearPointNow(p->pos().x(), p->pos().y()+speed);  //存下當前座標格子點
                    }
                }
            }
            else if(direct ==4){  //右
                FindNearPointMove(p->pos().x()+speed, p->pos().y());  //找欲移動的位置與點點最接近的點
                if(MainWindow::pos[ix1][jy1].CanMove == true ){  //如果最接近點(欲移動的位置)沒有障礙物
                    if(p->pos().x()+speed > MainWindow::pos[ix1][16].x){  //如果欲移動的位置超出邊界
                        if(ix1 == 9){  //如果在互通的地方
                            p->setX(p->pos().x() + speed);
                            FindNearPointNow(p->pos().x()+speed, p->pos().y());  //存下當前座標格子點
                            p->setX(MainWindow::pos[9][0].x + speed);  //從另一邊進來
                            FindNearPointNow(MainWindow::pos[9][0].x + speed, p->pos().y());  //存下當前座標格子點
                        }
                        else{
                            p->setX(MainWindow::pos[ix1][jy1].x);  //停在邊界前
                            ix = ix1;  //存下當前座標格子點
                            jy = jy1;
                            orangeRecursive();
                        }
                    }
                    else if(MainWindow::pos[ix1][jy1+1].CanMove == false && p->pos().x()+speed > MainWindow::pos[ix1][jy1].x){  //如果欲移動到的點有牆壁
                        p->setX(MainWindow::pos[ix1][jy1].x);  //停在牆壁前
                        ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else if(MainWindow::DotExist[ix1][jy1] == 2 && p->pos().x()+speed > MainWindow::pos[ix1][jy1].x){
                        p->setX(p->pos().x() + speed);  //移動
                        ix = ix1;  //存下當前座標格子點
                        jy = jy1;
                        orangeRecursive();
                    }
                    else{
                        p->setX(p->pos().x() + speed);  //移動
                        FindNearPointNow(p->pos().x()+speed, p->pos().y());  //存下當前座標格子點
                    }
                }
            }
       }
}



int ghostOrange::MoveRuleOrange(int changeX, int changeY, int changeMap[20][17], int distance)
{
    if((changeX == MainWindow::pac->ix && changeY == MainWindow::pac->jy) || (distance > 20)){  //如果鬼找到小精靈
        return distance;  //回傳總長度
    }
    int minDistance = 100;
    int distanceTmp[4] = {0};
    int derectTmp = changeMap[changeX][changeY];
    changeMap[changeX][changeY] = 0;//更改原地圖，將原本的點設成牆壁(0:有牆壁，1:沒牆壁)
    if(changeMap[changeX-1][changeY] == true && changeX > 0){  //如果往上沒牆壁
        distanceTmp[0] = MoveRuleOrange(changeX-1, changeY, changeMap, distance+1);
    }
    if(changeMap[changeX+1][changeY] == true && changeX < 19){  //如果往下沒牆壁
        distanceTmp[2] = MoveRuleOrange(changeX+1, changeY, changeMap, distance+1);
    }
    if(changeMap[changeX][changeY-1] == true && changeY > 0){  //如果往左沒牆壁
        distanceTmp[1] = MoveRuleOrange(changeX, changeY-1, changeMap, distance+1);
    }
    if(changeMap[changeX][changeY+1] == true && changeY < 16){  //如果往右沒牆壁
        distanceTmp[3] = MoveRuleOrange(changeX, changeY+1, changeMap, distance+1);
    }
    changeMap[changeX][changeY] = derectTmp;
    for(int i=0; i<4; ++i){
        if((distanceTmp[i] < minDistance) && distanceTmp[i]>0){
            minDistance = distanceTmp[i];
            directTmp = i+1;
        }
    }
    return minDistance;

}

int ghostOrange::MoveRuleOrangeHome(int changeX, int changeY, int changeMap[20][17], int distance)
{
    if((changeX == 19 && changeY == 0) || (distance > 20)){  //如果鬼找到小精靈
        return distance;  //回傳總長度
    }

        int minDistance = 100;
            int distanceTmp[4] = {0};
            int derectTmp = changeMap[changeX][changeY];
            changeMap[changeX][changeY] = 0;//更改原地圖，將原本的點設成牆壁(0:有牆壁，1:沒牆壁)
            if(changeMap[changeX-1][changeY] == true && changeX > 0){  //如果往上沒牆壁
                distanceTmp[0] = MoveRuleOrangeHome(changeX-1, changeY, changeMap, distance+1);
            }
            if(changeMap[changeX+1][changeY] == true && changeX < 19){  //如果往下沒牆壁
                distanceTmp[2] = MoveRuleOrangeHome(changeX+1, changeY, changeMap, distance+1);
            }

            if(changeMap[changeX][changeY-1] == true && changeY > 0){  //如果往左沒牆壁
                distanceTmp[1] = MoveRuleOrangeHome(changeX, changeY-1, changeMap, distance+1);
            }
            if(changeMap[changeX][changeY+1] == true && changeY < 16){  //如果往右沒牆壁
                distanceTmp[3] = MoveRuleOrangeHome(changeX, changeY+1, changeMap, distance+1);
            }
            changeMap[changeX][changeY] = derectTmp;
            for(int i=0; i<4; ++i){
                if((distanceTmp[i] < minDistance) && distanceTmp[i]>0){
                    minDistance = distanceTmp[i];
                    direct = i+1;
                }
            }
            return minDistance;


}

void ghostOrange::orangeRecursive()
{
    int line = MoveRuleOrange(ix, jy, WallTmp, 0);  //呼叫recursive判斷最短路徑
    if(line > 8){
        direct = directTmp;
    }
    else {
        MoveRuleOrangeHome(ix, jy ,WallTmp, 0);
    }
}
void ghostOrange::calls()
{
    if(p->collidesWithItem(MainWindow::pac->p)){  //如果鬼找到小精靈
        //qDebug()<<MainWindow::pac->pelletEat;
        if(MainWindow::pac->pelletEat == true){
            p->hide();
            direct = 0;
            p->setPos(MainWindow::pos[8][7].x, MainWindow::pos[8][7].y+10);
            orangeGoHome->start(5000);
/*            p->show();
            BeginMove = true;
            direct = 4;
*/        }
        else {
            MainWindow::pac->direct = 0;
            //MainWindow::pac->p->setPos(10000, 10000);
            MainWindow::pac->p->hide();  //小精靈被吃掉
            MainWindow::red->p->hide();
            MainWindow::pink->p->hide();
            MainWindow::blue->p->hide();
            MainWindow::orange->p->hide();
            MainWindow::lab->setText("Lose");
        }
    }
    move();  //呼叫移動的規則，讓精靈持續移動
}
