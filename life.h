#ifndef LIFE_H
#define LIFE_H

#include <QGraphicsView>
#include<QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "player.h"

class Life : public QObject, public QGraphicsPixmapItem
{
    float xVelocity = 0;
    float maxspeed = 5;
    float acceleration = 0.4;

public:
    Life(QGraphicsItem * parent = nullptr, int x = 0);

    float getXVelocity() const;
    void setXVelocity(float newXVelocity);

    float getMaxspeed() const;
    void setMaxspeed(float newMaxspeed);

    float getAcceleration() const;
    void setAcceleration(float newAcceleration);

public slots:
    // void moveRightWithPlayer(Player * player);
    // void moveLeftWithPlayer(Player * player);
};

#endif // LIFE_H
