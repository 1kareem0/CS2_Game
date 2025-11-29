#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include "block.h"
#include "obstacle.h"
#include "checkpoint.h"
#include <QKeyEvent>
#include <QTimer>

class Player : public QObject ,public QGraphicsPixmapItem
{
    Q_OBJECT
    float yVelocity = 0;
    float xVelocity = 0;
    float maxspeed = 5;
    float gravity = 0.5;
    bool isOnGround;
    bool jumping;
    float acceleration = 0.4;
    bool running_forward = false;
    bool running_backward = false;
    int lives = 3;
    QPointF lastcheckpoint;

    friend class level;

public:
    Player(QGraphicsItem * parent = nullptr);

    void setLives(int newLives);
    void setLastcheckpoint(QPointF newLastcheckpoint);

    int getLives() const;
    QPointF getLastcheckpoint() const;

signals:
    void scrollWorldLeft(int speed);
    void scrollWorldRight(int speed);
    void restartLevel();
    void restartFromCheckpoint();

public slots:
    bool onBlock();
    void fall();
    void jump();
    void move_right();
    void move_left();
    void damage();
    //bool predictCollision(float newX, float newY);
    //void snapPlayerRight();
    bool hitObstacle();
    void hitCheckpoint();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // PLAYER_H
