#include "block.h"



Block::Block(QGraphicsItem *parent, int x)
{
    setPixmap(QPixmap(":/assets/Dirt_Block.png"));
    this->setPos(-30 + x, 400);
    this->setScale(1.5);
}

Block::Block(const QPixmap &pixmap, QGraphicsItem *parent, int x)
{
    setPixmap(QPixmap(pixmap));
    this->setPos(-30 + x, 400);
}
