#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QList>
#include "block.h"

class Player;  // Forward declaration

class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int speed;
    int direction;
    double yVelocity;
    double gravity;
    double leftBound;
    double rightBound;
    bool canFall;
    QList<Block*> blocks;  // Reference to blocks for collision detection

public:
    enemy(QGraphicsItem *parent = nullptr, double startX = 0, double startY = 0);

    // Physics
    void fall();
    bool onBlock();

    // Movement and boundaries
    void checkBoundaries();
    // void checkEdges();  // Check for platform edges to turn around
    void reverseDirection();

    // Collision
    void checkPlayerCollision();

    // Setters
    void setBlocks(const QList<Block*>& b);
    void setBounds(double left, double right);

public slots:
    void move();

signals:
    void hitPlayer();
    void enemyDestroyed();
};

#endif // ENEMY_H
