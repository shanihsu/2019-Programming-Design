#ifndef KING_H
#define KING_H
#include "chess.h"
#include "track_mouse.h"
class king:public chess
{
public:
    king(QIcon i, MainWindow *w, QGraphicsView *v, struct position p, bool color);
    bool judgeKingRule();
    bool kingSeeKing();  //判斷是否王見王
public slots:
    void click_chess();  //點擊棋子後會發生的事
};

#endif // KING_H
