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
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &enemy::move);
    moveTimer->start(16);

    // Gravity timer
    fallTimer = new QTimer(this);
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
            QRectF enemyR = this->boundingRect().translated(this->pos());
            QRectF blockR = block->boundingRect().translated(block->pos());
            if(enemyR.bottom() <= blockR.top() + block->getBlockTop()){
                return true;
            }
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

void enemy::setBlocks(const QList<Block *> &b)
{
    blocks = b;
}

void enemy::setBounds(double left, double right)
{
    leftBound = left;
    rightBound = right;
}

enemy::~enemy()
{
    delete moveTimer;
    delete fallTimer;
}

void enemy::move()
{
    setPos(x() + direction * speed, y());
    //checkBoundaries(); //when we add static objects
}
