#ifndef CAR_H
#define CAR_H
#include "chess.h"

class car:public chess
{
public:
    car(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color);
    bool judgeCarRule();
    bool kingSeeKing();  //判斷是否王見王
public slots:
    void click_chess();  //點擊棋子後會發生的事
};

#endif // CAR_H
