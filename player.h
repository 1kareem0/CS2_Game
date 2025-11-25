#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include "block.h"
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

public:
    Player(QGraphicsItem * parent = nullptr);

public slots:
    bool onBlock();
    void fall();
    void jump();
    void move_right();
    void move_left();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // PLAYER_H
