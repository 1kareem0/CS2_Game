#include "life.h"

Life::Life(QGraphicsItem *parent, int x)
{
    setPixmap(QPixmap(":/assets/Finn_life.png"));
    setScale(0.4);
    setPos(30 + x ,10);
}
