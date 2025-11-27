#include "player.h"
#include "game.h"

Player::Player(QGraphicsItem * parent) {
    setPixmap(QPixmap(":/assets/Finn2.png"));
    this->setPos(30, 300);
    this->setScale(0.4);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    QTimer * running = new QTimer(this);
    running->start(16);
    connect(running, &QTimer::timeout, this, &Player::move_right);
    connect(running, &QTimer::timeout, this, &Player::move_left);
}

bool Player::onBlock()
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

void Player::fall()
{

    if(!onBlock() || jumping){
        yVelocity += gravity;
        this->setPos(x(), y()+yVelocity);
        if(onBlock()){
            yVelocity = 0;
            isOnGround = true;
            jumping = false;
        }
        //I removed return form if
    }
    else
        isOnGround = true; // This is to allow the player to jump again, without it the player will get permission to jump while in the air
}

void Player::jump()
{
    if(isOnGround){
        yVelocity = -10;
        isOnGround = false;
        jumping = true;
    }
}

void Player::move_right()
{
    int middleX = 540; // middle of screen
    int speed = 0;

    if(running_forward){
        xVelocity += acceleration;
        if(xVelocity > maxspeed){
            xVelocity = maxspeed;
        }
        if (x() < middleX) {
            setPos(x() + xVelocity, y());  //normal until reaching middle
        } else {
            emit scrollWorldLeft(xVelocity);  //in middle, scroll the world instead
        }
    }
    else if(!running_forward && !running_backward){
        xVelocity -= acceleration;
        if(xVelocity < 0){
            xVelocity = 0;
        }
        setPos(x() + xVelocity, y());
    }
}

void Player::move_left()
{
    int position = 200;

    if(running_backward){
        xVelocity += acceleration;
        if(xVelocity > maxspeed){
            xVelocity = maxspeed;
        }
        if(x() > position){
            setPos(x() - xVelocity, y());
        }
        else {
            emit scrollWorldRight(xVelocity);
        }
    }
    else if(!running_backward && !running_forward){
        xVelocity -= acceleration;
        if(xVelocity < 0){
            xVelocity = 0;
        }
         setPos(x() - xVelocity, y());
    }
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        jump();
    }
    else if(event->key() == Qt::Key_Right){
        running_forward = true;
    }
    else if(event->key() == Qt::Key_Left){
        running_backward = true;
    }
    else{
        QGraphicsPixmapItem::keyPressEvent(event);
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right){
        running_forward = false;
    }
    else if(event->key() == Qt::Key_Left){
        running_backward = false;
    }
}


