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
    bool isEnd = false;

public:
    checkpoint(QGraphicsItem *parent, float x, float y, bool isEnd);
    bool getIsEnd() const;
    void setIsEnd(bool newIsEnd);
};

#endif // CHECKPOINT_H
