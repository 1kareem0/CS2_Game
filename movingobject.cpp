#include "MovingObject.h"

MovingObject::MovingObject(QTimer* gameTimer,  int left,  int right,  const QList<QPixmap>& frames,  int frameInterval,  QGraphicsItem* parent)
    : Obstacle(frames, frameInterval, parent),
    leftLimit(left), rightLimit(right)
{
    connect(gameTimer, &QTimer::timeout, this, &MovingObject::updateMovement);
}


void MovingObject::updateMovement()
{
    if (movingRight)
    {
        velocity += acceleration;
        if (velocity > maxSpeed) velocity = maxSpeed;

        setPos(x() + velocity, y());

        if (x() >= rightLimit)
        {
            movingRight = false;
            velocity = 0;
        }
    }
    else
    {
        velocity += acceleration;
        if (velocity > maxSpeed) velocity = maxSpeed;

        setPos(x() - velocity, y());

        if (x() <= leftLimit)
        {
            movingRight = true;
            velocity = 0;
        }
    }
}
