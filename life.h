#ifndef LIFE_H
#define LIFE_H

#include <QGraphicsView>
#include<QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Life : public QObject, public QGraphicsPixmapItem
{
public:
    Life(QGraphicsItem * parent = nullptr, int x = 0);
};

#endif // LIFE_H
