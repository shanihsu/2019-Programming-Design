#include "ghost.h"
#include <mainwindow.h>
#include <QDebug>

ghost::ghost()
{
    timePellet = new QTimer();
    connect(timePellet, &QTimer::timeout, [](){
        if(MainWindow::pac->pelletEat == true){
            MainWindow::pac->pelletEat = false;
            MainWindow::red->map.load(":/img/jpg/red.png");
            MainWindow::red->p->setPixmap(MainWindow::red->map);
            MainWindow::red->p->setScale(0.085);
            MainWindow::red->p->setOffset(-MainWindow::red->map.width()/2, -MainWindow::red->map.height()/2);
            MainWindow::red->speed = 8;
            MainWindow::blue->map.load(":/img/jpg/blue.png");
            MainWindow::blue->p->setPixmap(MainWindow::blue->map);
            MainWindow::blue->p->setScale(0.085);
            MainWindow::blue->p->setOffset(-MainWindow::blue->map.width()/2, -MainWindow::blue->map.height()/2);
            MainWindow::blue->speed = 8;
            MainWindow::pink->map.load(":/img/jpg/pink.png");
            MainWindow::pink->p->setPixmap(MainWindow::pink->map);
            MainWindow::pink->p->setScale(0.085);
            MainWindow::pink->p->setOffset(-MainWindow::pink->map.width()/2, -MainWindow::pink->map.height()/2);
            MainWindow::pink->speed = 8;
            MainWindow::orange->map.load(":/img/jpg/orange.png");
            MainWindow::orange->p->setPixmap(MainWindow::orange->map);
            MainWindow::orange->p->setScale(0.085);
            MainWindow::orange->p->setOffset(-MainWindow::orange->map.width()/2, -MainWindow::orange->map.height()/2);
            MainWindow::orange->speed = 8;
        }
    });
    direct = 4;  //給定初始方向向右
    speed = 8;  //定義速度
    callMove = new QTimer();  //生成計時器
    callMove->setInterval(100);  //定義計時器週期為100毫秒,發出timeout()的訊號
    connect(callMove, SIGNAL(timeout()), this, SLOT(calls()));
    //每100毫秒計時器傳送訊號給calls函式，讓小精靈可以持續以週期為100毫秒持續移動
    qDebug()<<"calljfj";
    callMove->start();  //設定週期
    for(int i=0; i<20; ++i){
        for(int j=0; j<17; ++j){
            WallTmp[i][j] = MainWindow::pos[i][j].CanMove;  //存下地圖(0:有牆壁，1:沒牆壁)
        }
    }
}

void ghost::move()  //定義鍵盤移動方向
{

}

void ghost::FindNearPointNow(float xx, float yy)
{
    float r = 0;  //欲移動到的點與點點的距離
    float d = 10000;  //欲移動到的點與點點的距離最小值
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

void ghost::FindNearPointMove(float xx, float yy)  //找欲移動到的點與小精靈的最接近點
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

void ghost::calls()
{
    qDebug()<<"call";
    if(p->collidesWithItem(MainWindow::pac->p)){  //如果鬼找到小精靈
        //qDebug()<<MainWindow::pac->pelletEat;
        if(MainWindow::pac->pelletEat == true){
            p->hide();
            direct = 0;

        }
        else {
            MainWindow::pac->direct = 0;
            //MainWindow::pac->p->setPos(10000, 10000);
            MainWindow::pac->p->hide();  //小精靈被吃掉
        }

    }
    move();  //呼叫移動的規則，讓精靈持續移動
}

