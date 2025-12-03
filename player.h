#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include "block.h"
#include "obstacle.h"
#include "checkpoint.h"
#include "coin.h"
#include <QKeyEvent>
#include <QTimer>
#include<cmath>
#include "life.h"

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
    std::vector<Life *> lives;
    QPointF lastcheckpoint;
    static int totalCoins;

    friend class level;

public:
    Player(QGraphicsItem * parent = nullptr);

    void setLastcheckpoint(QPointF newLastcheckpoint);

    QPointF getLastcheckpoint() const;

    static int getTotalCoins();
    static void addCoins(int amount);
    static void resetCoins(); //the coins will be updated when the player die
    std::vector<Life *> getLives();
    void setLives(const std::vector<Life *> &newLives);
    void resetLives();

signals:
    // void scrollWorldLeft(int speed);
    // void scrollWorldRight(int speed);
    void restartLevel();
    void restartFromCheckpoint();
    void reduceLife();
    void CenterOnPlayer();

public slots:
    bool onBlock();
    void fall();
    void jump();
    void move_right();
    void move_left();
    void damage();
    bool hitObstacle();
    void hitCheckpoint();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // PLAYER_H
