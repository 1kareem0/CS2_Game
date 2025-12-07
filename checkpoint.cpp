#include "checkpoint.h"

bool checkpoint::getIsEnd() const
{
    return isEnd;
}

void checkpoint::setIsEnd(bool newIsEnd)
{
    isEnd = newIsEnd;
}

checkpoint::checkpoint(QGraphicsItem *parent, float x, float y, bool isEnd) : QGraphicsPixmapItem(parent)
{
    setIsEnd(isEnd);
    setPixmap(QPixmap(":/assets/Flag.png"));
    setPos(x, y);
}
