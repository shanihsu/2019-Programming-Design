#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QPushButton>
#include "track_mouse.h"
#include "chess.h"
#include "soldier.h"
#include "car.h"
#include "elephant.h"
#include "guard.h"
#include "horse.h"
#include "king.h"
#include "pown.h"
#include <QDebug>
#include <QImage>
struct position MainWindow::pos[10][9];
struct position MainWindow::kingData[2];
bool MainWindow::clickColor;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);          //設定背景
    QPixmap board(":/img/jpg/board.gif");       //匯入棋盤
    board = board.scaled(ui->graphicsView->width()-2,ui->graphicsView->height()-2);  //調整棋盤大小
    scene->addPixmap(board);
    connect(ui->graphicsView, SIGNAL(sendsignal(struct position)), this, SLOT(ShowMousePosition(struct position)));  //偵測滑鼠在棋盤上移動的訊號
    struct position beginPoint;         //存下棋盤格子點座標
    beginPoint.x = 149;
    beginPoint.y = 110;
    int dx = 61;  //兩橫線距離
    int dy = 67;  //兩直線距離
    for(int i=0; i<10; ++i){
        for(int j=0; j<9; ++j){
            pos[i][j].x = beginPoint.x+j*dy;
            pos[i][j].y = beginPoint.y+i*dx;
            pos[i][j].x1 = i;
            pos[i][j].y1 = j;
        }
    }

    for(int i=0; i<5; ++i){          //匯入棋子,並存下那點棋子
        this->pos[6][2*i].che = new soldier(QIcon(":/img/jpg/紅兵.png"),this, ui->graphicsView, pos[6][2*i], false);
        this->pos[3][2*i].che = new soldier(QIcon(":/img/jpg/黑卒.png"),this, ui->graphicsView, pos[3][2*i], true);
    }
    for(int i=0; i<3; ++i){
        this->pos[7][1+3*i].che = new pown(QIcon(":/img/jpg/紅包.png"),this, ui->graphicsView, pos[7][1+3*i], false);
        this->pos[2][1+3*i].che = new pown(QIcon(":/img/jpg/黑包.png"),this, ui->graphicsView, pos[2][1+3*i], true);
        this->pos[9][1+3*i].che = new horse(QIcon(":/img/jpg/紅馬.png"),this, ui->graphicsView, pos[9][1+3*i], false);
        this->pos[0][1+3*i].che = new horse(QIcon(":/img/jpg/黑馬.png"),this, ui->graphicsView, pos[0][1+3*i], true);
        i = i+1;
    }
    for(int i=1; i<3; ++i){
        this->pos[9][1+2*i].che = new guard(QIcon(":/img/jpg/紅士.png"),this, ui->graphicsView, pos[9][1+2*i], false);
        this->pos[0][1+2*i].che = new guard(QIcon(":/img/jpg/黑士.png"),this, ui->graphicsView, pos[0][1+2*i], true);
    }
    for(int i=1; i<4; ++i){
        this->pos[9][2*i].che = new elephant(QIcon(":/img/jpg/紅相.png"),this, ui->graphicsView, pos[9][2*i], false);
        this->pos[0][2*i].che = new elephant(QIcon(":/img/jpg/黑象.png"),this, ui->graphicsView, pos[0][2*i], true);
        i = i+1;
    }
    for(int i=0; i<2; ++i){
        this->pos[9][8*i].che = new car(QIcon(":/img/jpg/紅車.png"),this, ui->graphicsView, pos[9][8*i], false);
        this->pos[0][8*i].che = new car(QIcon(":/img/jpg/黑車.png"),this, ui->graphicsView, pos[0][8*i],true);
    }
    this->pos[9][4].che = new king(QIcon(":/img/jpg/紅帥.png"),this, ui->graphicsView, pos[9][4], false);
    this->pos[0][4].che = new king(QIcon(":/img/jpg/黑將.png"),this, ui->graphicsView, pos[0][4], true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowMousePosition(struct position poss)   //印出滑鼠位置
{
    ui->label->setText("x: " + QString::number(poss.x) + ",y: " + QString::number(poss.y));
}

void MainWindow::recieveKingSignal()  //接收叫出判斷輸贏的圖片時機的訊號
{
    if(kingData[0].ChessExist == false && kingData[1].ChessExist == true)  //如果黑將不存在
    {
        ui->label_2->setPixmap(QPixmap(":/img/jpg/black lose.png"));  //叫出黑輸的圖片
        ui->label_2->setScaledContents(true);
        ui->label_2->raise();
    }
    else if(kingData[0].ChessExist == true && kingData[1].ChessExist == false){  //如果紅帥不存在
        ui->label_3->setPixmap(QPixmap(":/img/jpg/black win.png"));  //叫出紅輸的圖片
        ui->label_3->setScaledContents(true);
        ui->label_3->raise();
    }
}
