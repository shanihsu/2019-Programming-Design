#include "pacman.h"
#include <mainwindow.h>
#include <QDebug>
pacman::pacman()
{
    map.load(":/img/jpg/man_right.png");
    p = new QGraphicsPixmapItem(map);  //設定小精靈物件
    p->setScale(0.17);  //設定小精靈大小
    p->setPos(MainWindow::pos[11][7].x, MainWindow::pos[11][7].y);  //設定小精靈初始位置
    ix = 11;
    jy = 7;
    p->setOffset(-map.width()/2, -map.height()/2);  //將小精靈的中心點對準點點
    speed = 10;  //定義速度
    callMove = new QTimer();  //生成計時器
    callMove->setInterval(100);  //定義計時器週期為100毫秒,發出timeout()的訊號
    connect(callMove, SIGNAL(timeout()), this, SLOT(calls()));
    //每100毫秒計時器傳送訊號給calls函式，讓小精靈可以持續以週期為100毫秒持續移動
    callMove->start();  //設定週期

}

void pacman::move()  //定義鍵盤移動方向
{
    if(direct == 1){  //上
        FindNearPointMove(p->pos().x(), p->pos().y()-speed);  //找欲移動的位置與點點最接近的點
        if(MainWindow::pos[ix1][jy1].CanMove == true){  //如果最接近點(欲移動的位置)沒有障礙物
            map.load(":/img/jpg/man_up.png");  //轉向
            p->setPixmap(map);
            if(p->pos().y()-speed < MainWindow::pos[0][jy1].y){  //如果欲移動的位置超出邊界
                  p->setY(MainWindow::pos[ix1][jy1].y);  //停在邊界前
                  ix = ix1;  //存下當前座標格子點
                  jy = jy1;
            }
            else if(MainWindow::pos[ix1-1][jy1].CanMove == false && p->pos().y()-speed < MainWindow::pos[ix1][jy1].y){  //如果欲移動到的點有牆壁
                p->setY(MainWindow::pos[ix1][jy1].y);  //停在牆壁前
                ix = ix1;  //存下當前座標格子點
                jy = jy1;
            }
            else{
                p->setY(p->pos().y() - speed);  //移動
                FindNearPointNow(p->pos().x(), p->pos().y()-speed);  //存下當前座標格子點
            }
        }
    }
    else if(direct ==2){  //左
        FindNearPointMove(p->pos().x()-speed, p->pos().y());  //找欲移動的位置與點點最接近的點
        if(MainWindow::pos[ix1][jy1].CanMove == true){  //如果最接近點(欲移動的位置)沒有障礙物
            map.load(":/img/jpg/man_left.png");  //轉向
            p->setPixmap(map);
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
                }
            }
            else if(MainWindow::pos[ix1][jy1-1].CanMove == false && p->pos().x()-speed < MainWindow::pos[ix1][jy1].x){  //如果欲移動到的點有牆壁
                p->setX(MainWindow::pos[ix1][jy1].x);  //停在牆壁前
                ix = ix1;  //存下當前座標格子點
                jy = jy1;
            }
            else{
                p->setX(p->pos().x() - speed);  //移動
                FindNearPointNow(p->pos().x()-speed, p->pos().y());  //存下當前座標格子點
            }
        }
    }
    else if(direct == 3){  //下
        FindNearPointMove(p->pos().x(), p->pos().y()+speed);  //找欲移動的位置與點點最接近的點
        if(MainWindow::pos[ix1][jy1].CanMove == true){  //如果最接近點(欲移動的位置)沒有障礙物
            map.load(":/img/jpg/man_down.png");  //轉向
            p->setPixmap(map);
            if(p->pos().y()+speed > MainWindow::pos[19][jy1].y){  //如果欲移動的位置超出邊界
                p->setY(MainWindow::pos[ix1][jy1].y);  //停在邊界前
                ix = ix1;  //存下當前座標格子點
                jy = jy1;
            }
            else if(MainWindow::pos[ix1+1][jy1].CanMove == false && p->pos().y()+speed > MainWindow::pos[ix1][jy1].y){  //如果欲移動到的點有牆壁
                p->setY(MainWindow::pos[ix1][jy1].y);  //停在牆壁前
                ix = ix1;  //存下當前座標格子點
                jy = jy1;
            }
            else{
                p->setY(p->pos().y() + speed);  //移動
                FindNearPointNow(p->pos().x(), p->pos().y()+speed); //存下當前座標格子點
            }
        }
    }
    else if(direct ==4){  //右
        FindNearPointMove(p->pos().x()+speed, p->pos().y());  //找欲移動的位置與點點最接近的點
        if(MainWindow::pos[ix1][jy1].CanMove == true ){  //如果最接近點(欲移動的位置)沒有障礙物
            map.load(":/img/jpg/man_right.png");  //轉向
            p->setPixmap(map);
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
                }
            }
            else if(MainWindow::pos[ix1][jy1+1].CanMove == false && p->pos().x()+speed > MainWindow::pos[ix1][jy1].x){  //如果欲移動到的點有牆壁
                p->setX(MainWindow::pos[ix1][jy1].x);  //停在牆壁前
                ix = ix1;  //存下當前座標格子點
                jy = jy1;
            }
            else{
                p->setX(p->pos().x() + speed);  //移動
                FindNearPointNow(p->pos().x()+speed, p->pos().y());  //存下當前座標格子點
            }
        }
    }
}
void pacman::FindNearPointMove(float xx, float yy)  //找欲移動到的點與小精靈的最接近點
{
    float r = 0;  //欲移動到的點與點點的距離
    float d = 10000;  //欲移動到的點與點點的距離最小值
    for(int i=0; i<20;++i){
       for(int j=0; j<17;++j){
               r = (MainWindow::pos[i][j].x-xx)*(MainWindow::pos[i][j].x-xx)+(MainWindow::pos[i][j].y-yy)*(MainWindow::pos[i][j].y-yy);
               r = sqrt(r);
               if(r<d){
                   d = r;
                   ix1 = i;
                   jy1 = j;
               }
       }
    }
}

void pacman::FindNearPointNow(float xx, float yy)  //找當前座標與小精靈的最接近點
{
    float r = 0;  //欲當前座標與點點的距離
    float d = 10000;  //欲當前座標與點點的距離最小值
    for(int i=0; i<20;++i){
       for(int j=0; j<17;++j){
               r = (MainWindow::pos[i][j].x-xx)*(MainWindow::pos[i][j].x-xx)+(MainWindow::pos[i][j].y-yy)*(MainWindow::pos[i][j].y-yy);
               r = sqrt(r);
               if(r<d){
                   d = r;
                   ix = i;
                   jy = j;
               }
       }
    }
}


void pacman::calls()
{
    QList <QGraphicsItem *> power = p->collidingItems();
    foreach(QGraphicsItem *i, power){
        powerPellet *pellet = dynamic_cast<powerPellet *>(i);
        if(pellet != nullptr){
            pellet->hide();
            pelletEat = true;
            MainWindow::red->map.load(":/img/jpg/ghostCollipse.png");
            MainWindow::red->p->setPixmap(MainWindow::red->map);
            MainWindow::red->p->setScale(0.125);
            MainWindow::red->p->setOffset(-MainWindow::red->map.width()/2, -MainWindow::red->map.height()/2);
            MainWindow::red->speed = 4;
            MainWindow::red->timePellet->start(5000);
            MainWindow::blue->map.load(":/img/jpg/ghostCollipse.png");
            MainWindow::blue->p->setPixmap(MainWindow::red->map);
            MainWindow::blue->p->setScale(0.125);
            MainWindow::blue->p->setOffset(-MainWindow::blue->map.width()/2, -MainWindow::blue->map.height()/2);
            MainWindow::blue->speed = 4;
            MainWindow::blue->timePellet->start(5000);
            MainWindow::pink->map.load(":/img/jpg/ghostCollipse.png");
            MainWindow::pink->p->setPixmap(MainWindow::red->map);
            MainWindow::pink->p->setScale(0.125);
            MainWindow::pink->p->setOffset(-MainWindow::pink->map.width()/2, -MainWindow::pink->map.height()/2);
            MainWindow::pink->speed = 4;
            MainWindow::pink->timePellet->start(5000);
            MainWindow::orange->map.load(":/img/jpg/ghostCollipse.png");
            MainWindow::orange->p->setPixmap(MainWindow::red->map);
            MainWindow::orange->p->setScale(0.125);
            MainWindow::orange->p->setOffset(-MainWindow::orange->map.width()/2, -MainWindow::orange->map.height()/2);
            MainWindow::orange->speed = 4;
            MainWindow::orange->timePellet->start(5000);
            scores = scores + 5;
            ++dotScore;
            MainWindow::lab->setNum(scores);  //加分
            if(dotScore == 189){
                MainWindow::lab->setText("Win");
            }
        }
    }
    QList <QGraphicsItem *> thing = p->collidingItems();
    foreach(QGraphicsItem *i, thing){
        QGraphicsEllipseItem *e = dynamic_cast<QGraphicsEllipseItem *>(i);
        if(e != nullptr){
            e->hide();
            ++dotScore;
            MainWindow::lab->setNum(++scores);  //加分
            if(dotScore == 189){
                MainWindow::lab->setText("Win");
            }

        }
    }
/*    if(p->collidingItems().size() == 2 &&
            ((!p->collidesWithItem(MainWindow::pink->p))&&
             (!p->collidesWithItem(MainWindow::red->p))&&
             (!p->collidesWithItem(MainWindow::orange->p))&&
             (!p->collidesWithItem(MainWindow::blue->p))))
    {  //如果有背景迷宮跟點點兩個物件
        //p->collidingItems().at(0)->hide();  //把點點吃掉
        //MainWindow::lab->setNum(++scores);  //加分

    }
*/
    move();  //呼叫移動的規則，讓精靈持續移動
}
