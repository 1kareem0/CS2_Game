#include "enemy.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include "block.h"
#include "player.h"
enemy::enemy(QGraphicsItem *parent): QGraphicsPixmapItem(parent), speed(2), direction(-1),yVelocity(0),
    gravity(0.5), leftBound(0), rightBound(0)
{
 setPixmap(QPixmap(":/assets/Lich.png"));
 setScale(0.25);

 leftBound = x() - 300;
 rightBound = x() + 300;

 QTimer *moveTimer = new QTimer(this);
 connect(moveTimer, &QTimer::timeout, this, &enemy::move);
 moveTimer->start(16);

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

void enemy::checkPlayerCollision()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    for(auto item : collisions){
        Player * player = dynamic_cast<Player *>(item);
        if(player){
            emit hitPlayer();
            return;
        }
    }
}

void enemy::move()
{
    setPos(x() + direction * speed, y());
    checkPlayerCollision();
    //checkBoundaries(); //when we add static objects
}
