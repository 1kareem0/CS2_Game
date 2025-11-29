#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class enemy : public QObject ,public QGraphicsPixmapItem
{
    Q_OBJECT
    int speed;
    int direction;
    double yVelocity;
    double gravity;
    double leftBound;
    double rightBound;

public:
    enemy(QGraphicsItem *parent = nullptr);
    void fall();
    bool onBlock();
    //After getting the sattic obstacles
    // void checkBoundaries();
    // void reverseDirection();
    void checkPlayerCollision();
public slots:
    void move();

signals:
    void hitPlayer();
};

#endif // ENEMY_H
