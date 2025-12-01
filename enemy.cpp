#include "enemy.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include "block.h"
#include "player.h"

enemy::enemy(QGraphicsItem *parent, double startX, double startY)
    : QGraphicsPixmapItem(parent),
    speed(2), direction(-1), yVelocity(0), gravity(0.5), leftBound(0), rightBound(0), canFall(true)
{
    setPixmap(QPixmap(":/assets/Lich.png"));
    setScale(0.25);

    setPos(startX, startY);

    leftBound = startX - 300;
    rightBound = startX + 300;

    // Movement timer
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &enemy::move);
    moveTimer->start(16);

    // Gravity timer
    QTimer *fallTimer = new QTimer(this);
    connect(fallTimer, &QTimer::timeout, this, &enemy::fall);
    fallTimer->start(16);
}
void enemy::fall()
{
    if(!onBlock()){
        yVelocity += gravity;
        setPos(x(), y() + yVelocity);
    }
    else{
        yVelocity = 0;
    }
}

//for dealing with gravity as an enemy
bool enemy::onBlock()
{
QList<QGraphicsItem *> collisions = collidingItems();
    for(auto item : collisions){
        Block * block = dynamic_cast<Block *>(item);
        if(block){
            return true;
        }
    }
    return false;
}

void enemy::checkBoundaries()
{
    if (x() <= leftBound && direction == -1) {
        reverseDirection();
        setX(leftBound);
    } else if (x() >= rightBound && direction == 1) {
        reverseDirection();
        setX(rightBound);
    }
}

void enemy::reverseDirection()
{
    direction *= -1;
}

void enemy::checkPlayerCollision()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    for (auto item : collisions) {
        Player *player = dynamic_cast<Player *>(item);
        if (player) {
            QRectF playerRect = player->boundingRect().translated(player->pos());
            QRectF enemyRect = boundingRect().translated(pos());

            if (playerRect.bottom() < enemyRect.center().y()) {
                // Player defeated enemy by jumping on it
                emit enemyDestroyed();
                scene()->removeItem(this);
                deleteLater();
                return;
            } else {
                // Enemy hit player from side
                emit hitPlayer();
            }
            return;
        }
    }
}

void enemy::setBlocks(const QList<Block *> &b)
{
    blocks = b;
}

void enemy::setBounds(double left, double right)
{
    leftBound = left;
    rightBound = right;
}

void enemy::move()
{
    setPos(x() + direction * speed, y());
    checkPlayerCollision();
    //checkBoundaries(); //when we add static objects
}
