#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "Obstacle.h"
#include <QTimer>

class MovingObject : public Obstacle
{
    Q_OBJECT

    float velocity = 0;
    float acceleration = 0.25;
    float maxSpeed = 3;

    int leftLimit;
    int rightLimit;

    bool movingRight = true;

public:
    MovingObject(QTimer* gameTimer, int leftLimit, int rightLimit, const QList<QPixmap>& frames, int frameInterval = 100, QGraphicsItem* parent = nullptr);

public slots:
    void updateMovement();
};

#endif // MOVINGOBJECT_H
