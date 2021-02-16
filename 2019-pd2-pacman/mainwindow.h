#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "pacman.h"
#include <QKeyEvent>
#include <QLabel>
#include "math.h"
#include "ghost.h"
#include "ghostpink.h"
#include "ghostred.h"
#include "ghostblue.h"
#include "ghostorange.h"
#include "powerpellet.h"

struct position{
    float x, y;  //xy座標
    bool CanMove;  //判斷是否可移動,0:false,1:true
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    static struct position pos[20][17]; //每個點的資料
    static int DotExist[20][17];  //各點是否有牆壁,0:有,1:沒有
    static pacman *pac;  //小精靈
    static ghostRed *red;
    static ghostPink *pink;
    static ghostBlue *blue;
    static ghostOrange *orange;
//    static ghost *ghostBlue, *ghostRed, *ghostPink, *ghostOrange;
    static QLabel *lab;  //記分板
    void keyPressEvent(QKeyEvent *key_event);  //鍵盤事件
    void FindNearPoint();  //找小精靈與點點最接近點
    int ix, jy;  //最接近點的第[ix][jy]點(當前座標)
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
