#include "block.h"


float Block::getBlockTop() const
{
    return BlockTop;
}

void Block::setBlockTop(float newBlockTop)
{
    BlockTop = newBlockTop;
}

Block::Block() {}

Block::Block(const QPixmap &pixmap, QGraphicsItem *parent, float Top) :  QGraphicsPixmapItem(pixmap, parent)
{
    setPixmap(QPixmap(pixmap));
    setBlockTop(Top);
}
