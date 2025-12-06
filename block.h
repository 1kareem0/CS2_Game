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
    float BlockTop;

public:
    Block();
    Block(const QPixmap& pixmap, QGraphicsItem* parent = nullptr, float Top = 506);
    float getBlockTop() const;
    void setBlockTop(float newBlockTop);
};

#endif // BLOCK_H
