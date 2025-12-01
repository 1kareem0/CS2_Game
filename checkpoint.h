#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QGraphicsView>
#include<QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class checkpoint : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    checkpoint(QGraphicsItem *parent, float x, float y);
};

#endif // CHECKPOINT_H
