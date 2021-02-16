#ifndef TRACK_MOUSE_H
#define TRACK_MOUSE_H
#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include "mainwindow.h"

class track_mouse:public QGraphicsView
{
    Q_OBJECT
public:
    track_mouse(QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *event);

signals:
    void sendsignal(struct position);

};

#endif // TRACK_MOUSE_H
