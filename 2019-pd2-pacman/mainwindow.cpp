#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTransform>
#include "ghost.h"
struct position MainWindow::pos[20][17]; //每個點的資料
int MainWindow::DotExist[20][17]= {{2,1,1,2,1,1,1,2,0,2,1,1,1,2,1,1,2},  //各點是否有牆壁,0:有,1:沒有
                                   {1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
                                   {1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
                                   {2,1,1,2,1,2,1,2,1,2,1,2,1,2,1,1,2},
                                   {1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1},
                                   {2,1,1,2,0,2,1,2,0,2,1,2,0,2,1,1,2},
                                   {0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0},
                                   {0,0,0,1,0,2,1,2,1,2,1,2,0,1,0,0,0},
                                   {0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0},
                                   {1,1,1,2,1,2,0,0,0,0,0,2,1,2,1,1,1},
                                   {0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0},
                                   {0,0,0,1,0,2,1,1,1,1,1,2,0,1,0,0,0},
                                   {0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0},
                                   {2,1,1,2,1,2,1,2,0,2,1,2,1,2,1,1,2},
                                   {1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
                                   {2,2,0,2,1,2,1,2,1,2,1,2,1,2,0,2,2},
                                   {0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0},
                                   {2,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,2},
                                   {1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1},
                                   {2,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,2}

           };
pacman *MainWindow::pac;  //小精靈
ghostRed *MainWindow::red;
ghostPink *MainWindow::pink;
ghostBlue *MainWindow::blue;
ghostOrange *MainWindow::orange;
//ghost *MainWindow::ghostBlue, *MainWindow::ghostRed, *MainWindow::ghostPink, *MainWindow::ghostOrange;
QLabel *MainWindow::lab;  //記分板
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocus();  //讓方向鍵可運作
    QGraphicsScene *scene = new QGraphicsScene();  //設定背景
    scene->setSceneRect(0,0,ui->graphicsView->width()-2,ui->graphicsView->height()-2);
    ui->graphicsView->setScene(scene);
    QPixmap map(":/img/jpg/pacman_background.gif");  //匯入迷宮
    scene->addPixmap(map.scaled(ui->graphicsView->width()-2, ui->graphicsView->height()-2));
/*    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);          //設定背景
    QPixmap background(":/img/jpg/pacman_background.gif");       //匯入迷宮
    background = background.scaled(ui->graphicsView->width()-2,ui->graphicsView->height()-2);  //調整迷宮大小
    scene->addPixmap(background);*/
/*    DotExist[20][17] = {{2,1,1,2,1,1,1,2,0,2,1,1,1,2,1,1,2},  //各點是否有牆壁,0:有,1:沒有
                            {1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
                            {1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
                            {2,1,1,2,1,2,1,2,1,2,1,2,1,2,1,1,2},
                            {1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1},
                            {2,1,1,2,0,2,1,2,0,2,1,2,0,2,1,1,2},
                            {0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0},
                            {0,0,0,1,0,2,1,2,1,2,1,2,0,1,0,0,0},
                            {0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0},
                            {1,1,1,2,1,2,0,0,0,0,0,2,1,2,1,1,1},
                            {0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0},
                            {0,0,0,1,0,2,1,1,1,1,1,2,0,1,0,0,0},
                            {0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0},
                            {2,1,1,2,1,2,1,2,0,2,1,2,1,2,1,1,2},
                            {1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
                            {2,2,0,2,1,2,1,2,1,2,1,2,1,2,0,2,2},
                            {0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0},
                            {2,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,2},
                            {1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1},
                            {2,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,2}

    };*/
    for(int i=0; i<20; ++i){
        for(int j=0; j<17; ++j){
            pos[i][j].CanMove = DotExist[i][j];  //存下各點是否可移動
        }
    }
    for(int i=0; i<17; ++i){
        for(int j=0; j<4; ++j){
            pos[j][i].x = 38.5+42.5*i+6.5;  //存下點點位置
            pos[j][i].y = 35+34*j+6.5;
            if(pos[j][i].CanMove == true){  //如果該點可移動，就設置點點
                QGraphicsEllipseItem *c = new QGraphicsEllipseItem(38.5+42.5*i, 35+34*j, 13,13);  //創立點點
                scene->addItem(c);
                c->setBrush(Qt::white);  //點點變白色

            }
        }
        for(int j=1;j<3;++j){
            pos[j+3][i].x = 38.5+42.5*i+6.5;  //存下點點位置
            pos[j+3][i].y = 35+34*3+38*j+6.5;
            if(pos[j+3][i].CanMove == true){  //如果該點可移動，就設置點點
                QGraphicsEllipseItem *c = new QGraphicsEllipseItem(38.5+42.5*i, 35+34*3+38*j, 13,13);  //創立點點
                scene->addItem(c);
                c->setBrush(Qt::white);  //點點變白色

            }
        }

        for(int j=1;j<15;++j){
            pos[j+5][i].x = 38.5+42.5*i+6.5;  //存下點點位置
            pos[j+5][i].y = 35+34*3+38*2+38.5*j+6.5;
            if(pos[j+5][i].CanMove == true){  //如果該點可移動，就設置點點
                QGraphicsEllipseItem *c = new QGraphicsEllipseItem(38.5+42.5*i, 35+34*3+38*2+38.5*j, 13,13);  //創立點點
                scene->addItem(c);
                c->setBrush(Qt::white);  //點點變白色

            }
        }
    }  //創點點
    powerPellet *p1 = new powerPellet(38.5+42.5*0-9, 35+34*2-9, 30, 30);  //[2][0]
    scene->addItem(p1);
    p1->setBrush(Qt::white);  //點點變白色
    powerPellet *p2 = new powerPellet(38.5+42.5*16-9, 35+34*2-9, 30,30);  //[2][17]
    scene->addItem(p2);
    p2->setBrush(Qt::white);  //點點變白色
    powerPellet *p3 = new powerPellet(38.5+42.5*0-9, 35+34*3+38*2+38.5*10-9, 30, 30);  //[15][0]
    scene->addItem(p3);
    p3->setBrush(Qt::white);  //點點變白色
    powerPellet *p4 = new powerPellet(38.5+42.5*16-9, 35+34*3+38*2+38.5*10-9, 30, 30);  //[15][17]
    scene->addItem(p4);
    p4->setBrush(Qt::white);  //點點變白色
    qDebug()<<"hhh"<<pos[5][15].x;
    pac = new pacman();  //創立小精靈class
    scene->addItem(pac->p);  //匯入小精靈圖片
    blue =  new ghostBlue(QPixmap(":/img/jpg/blue.png"));
    scene->addItem(blue->p);
    pink =  new ghostPink(QPixmap(":/img/jpg/pink.png"));
    scene->addItem(pink->p);
    orange =  new ghostOrange(QPixmap(":/img/jpg/orange.png"));
    scene->addItem(orange->p);
    red =  new ghostRed(QPixmap(":/img/jpg/red.png"));
    scene->addItem(red->p);
    MainWindow::lab = ui->score;  //記分板


}

void MainWindow::keyPressEvent(QKeyEvent *key_event)  //鍵盤事件
{

    if(key_event->key() == Qt::Key_Up){  //方向鍵上
        FindNearPoint();  //找最接近的點(要在有點點的地方才能轉彎)
        pac->p->setX(pos[ix][jy].x);  //把小精靈設置到點點上
        pac->p->setY(pos[ix][jy].y);
//        pac->p->setRotation(270);
        if(pos[ix-1][jy].CanMove == true){  //如果上方沒有障礙物
            qDebug()<<"w";
            pac->direct = 1;  //定義方向
        }
//        pac->move();
    }
    if(key_event->key() == Qt::Key_Left){  //方向鍵左
        FindNearPoint();  //找最接近的點(要在有點點的地方才能轉彎)
        pac->p->setX(pos[ix][jy].x);  //把小精靈設置到點點上
        pac->p->setY(pos[ix][jy].y);
//        pac->p->setRotation(180);
        if(pos[ix][jy-1].CanMove == true){  //如果左方沒有障礙物
            qDebug()<<"a";
            pac->direct = 2;  //定義方向
        }
//        pac->move();
    }
    if(key_event->key() == Qt::Key_Down){  //方向鍵下
        FindNearPoint();  //找最接近的點(要在有點點的地方才能轉彎)
        pac->p->setX(pos[ix][jy].x);  //把小精靈設置到點點上
        pac->p->setY(pos[ix][jy].y);
//        pac->p->setRotation(90);
        if(pos[ix+1][jy].CanMove == true){  //如果下方沒有障礙物
            qDebug()<<"s";
            pac->direct = 3;  //定義方向
        }
//        pac->move();
    }
    if(key_event->key() == Qt::Key_Right){  //方向鍵右
        FindNearPoint();  //找最接近的點(要在有點點的地方才能轉彎)
        pac->p->setX(pos[ix][jy].x);  //把小精靈設置到點點上
        pac->p->setY(pos[ix][jy].y);
//        pac->p->setRotation(0);
        if(pos[ix][jy+1].CanMove == true){  //如果右方沒有障礙物
            qDebug()<<"d";
            pac->direct = 4;  //定義方向
        }
//        pac->move();
    }
}

void MainWindow::FindNearPoint()  //找小精靈與點點最接近點
{
    float r = 0;  //小精靈與點點的距離
    float d = 10000;  //小精靈與點點的距離最小值
    for(int i=0; i<20;++i){
       for(int j=0; j<17;++j){
           if(pos[i][j].CanMove == true){
               r = (pos[i][j].x-pac->p->pos().x())*(pos[i][j].x-pac->p->pos().x())+(pos[i][j].y-pac->p->pos().y())*(pos[i][j].y-pac->p->pos().y());
               r = sqrt(r);
               if(r<d){
                   d = r;
                   ix = i;
                   jy = j;
               }
           }
       }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
