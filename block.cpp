#include "block.h"


Block::Block() {}

Block::Block(const QPixmap &pixmap, QGraphicsItem *parent) :  QGraphicsPixmapItem(pixmap, parent)
{
    setPixmap(QPixmap(pixmap));
}
