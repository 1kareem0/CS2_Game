#include "checkpoint.h"

checkpoint::checkpoint(QGraphicsItem *parent, float x, float y) :  QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/assets/Flag.png"));
    setPos(x, y);
}
