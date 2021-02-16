#ifndef SOLDIER_H
#define SOLDIER_H
#include "chess.h"

class soldier:public chess
{
public:
    soldier(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color);
    bool judgeSoldierRule();
    bool kingSeeKing();  //判斷是否王見王
public slots:
    void click_chess();  //點擊棋子後會發生的事
};

#endif // SOLDIER_H
