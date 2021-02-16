#ifndef HORSE_H
#define HORSE_H
#include "chess.h"

class horse:public chess
{
public:
    horse(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color);
    bool judgeHorseRule();
    bool horseFeet();  //拐馬腳
    bool kingSeeKing();  //判斷是否王見王
public slots:
    void click_chess();  //點擊棋子後會發生的事
};

#endif // HORSE_H
