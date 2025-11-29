#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QGraphicsView>
#include<QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class checkpoint : public QObject, public QGraphicsPixmapItem
{

public:
    checkpoint(QGraphicsItem *parent , QPointF pos);
};

#endif // CHECKPOINT_H
