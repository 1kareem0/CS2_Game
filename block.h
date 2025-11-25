#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsView>
#include<QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Block : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Block(QGraphicsItem* parent = nullptr, int x = 0);
    Block(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);
};

#endif // BLOCK_H
