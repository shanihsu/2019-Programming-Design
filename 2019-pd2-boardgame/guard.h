#ifndef GUARD_H
#define GUARD_H
#include "chess.h"

class guard:public chess
{
public:
    guard(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color);
    bool judgeGuardRule();
    bool kingSeeKing();  //判斷是否王見王
public slots:
    void click_chess();  //點擊棋子後會發生的事
};

#endif // GUARD_H
