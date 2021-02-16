#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
class chess;
struct position{
    bool color = false;  //紅色:false,黑色:true
    bool ChessExist = false;  //記下該點是否有棋子
    int x, y;  //xy座標
    int x1, y1;  //格子點第[x1][y1]點
    chess *che;  //記下該點的棋子指標
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    static struct position pos[10][9];  //格子點
    static struct position kingData[2];  //王的資料,king[0]:黑色,king[1]:紅色
    static bool clickColor;  //滑鼠點到的棋子顏色
    ~MainWindow();

public slots:
    void ShowMousePosition(struct position);
    void recieveKingSignal();  //接收叫出判斷輸贏的圖片時機的訊號
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
