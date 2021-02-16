#ifndef ELEPHANT_H
#define ELEPHANT_H
#include "chess.h"
#include "track_mouse.h"
class elephant:public chess
{
public:
    elephant(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color);
    bool judgeElephantRule();
    bool ElephantEye();  //塞象眼
    bool kingSeeKing();  //判斷是否王見王
public slots:
    void click_chess();  //點擊棋子後會發生的事
};

#endif // ELEPHANT_H
