#include "life.h"

float Life::getXVelocity() const
{
    return xVelocity;
}

void Life::setXVelocity(float newXVelocity)
{
    xVelocity = newXVelocity;
}

float Life::getMaxspeed() const
{
    return maxspeed;
}

void Life::setMaxspeed(float newMaxspeed)
{
    maxspeed = newMaxspeed;
}

float Life::getAcceleration() const
{
    return acceleration;
}

void Life::setAcceleration(float newAcceleration)
{
    acceleration = newAcceleration;
}

Life::Life(QGraphicsItem *parent, int x)
{
    setPixmap(QPixmap(":/assets/Finn_life.png"));
    setScale(0.4);
    setPos(30 + x ,10);
}


