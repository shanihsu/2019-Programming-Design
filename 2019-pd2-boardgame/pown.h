#ifndef POW_H
#define POW_H
#include "chess.h"

class pown:public chess
{
public:
    pown(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color);
    bool judgePownRule();
    bool kingSeeKing();  //判斷是否王見王
public slots:
    void click_chess();
};

#endif // POW_H
