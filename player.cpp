#include "player.h"
#include "game.h"

int Player::totalCoins = 0;

void Player::setLastcheckpoint(QPointF newLastcheckpoint)
{
    lastcheckpoint = newLastcheckpoint;
}

QPointF Player::getLastcheckpoint() const
{
    return lastcheckpoint;
}

int Player::getTotalCoins()
{
      return totalCoins;
}

void Player::addCoins(int amount)
{
    totalCoins += amount;
}

void Player::resetCoins()
{
    totalCoins = 0;
}

// std::vector<Life *> Player::getLives()
// {
//     return lives;
// }

// void Player::setLives(const std::vector<Life *> &newLives)
// {
//     lives = newLives;
// }

// void Player::resetLives()
// {
//     for(int i = 0; i < 180; i += 60){
//         Life *life = new Life(nullptr, i);
//         lives.push_back(life);
//     }
// }

int Player::getLives() const
{
    return lives;
}

void Player::setLives(int newLives)
{
    lives = newLives;
}

Player::Player(QGraphicsItem * parent) {
    yVelocity = 0;
    setPixmap(QPixmap(":/assets/Finn2.png"));
    this->setPos(30, 200);
    this->setScale(0.4);
    this->lastcheckpoint.setX(30);
    this->lastcheckpoint.setY(200);
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
            QRectF playerR = this->boundingRect().translated(this->pos());
            QRectF blockR = block->boundingRect().translated(block->pos());
            if(playerR.bottom() <= blockR.top() + 503){
            return true;
            }
            }
        }
    return false;
}

void Player::fall()
{

    if(!onBlock() || jumping){
        yVelocity += gravity;
        this->setPos(x(), y()+yVelocity);
        if(onBlock() && yVelocity > 0){
            yVelocity = 0;
            isOnGround = true;
            jumping = false;
        }
        else if(onBlock() && yVelocity < 0){
            this->setPos(x(), y() - (yVelocity + 8));
            isOnGround = false;
        }
        else if( yVelocity == 0 && !onBlock()){
            isOnGround = false;
            jumping = false;
        }
    }
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
        // if (x() < middleX) {
        //     setPos(x() + xVelocity, y());  //normal until reaching middle
        // } else {
        //     emit scrollWorldLeft(xVelocity);  //in middle, scroll the world instead
        // }
        setPos(x() + xVelocity, y());
        //emit moveRightWithPlayer();
    }
    else if(!running_forward && !running_backward){
        xVelocity -= acceleration;
        if(xVelocity < 0){
            xVelocity = 0;
        }
        setPos(x() + xVelocity, y());
    }
    emit CenterOnPlayer();
}

void Player::move_left()
{
    int position = 200;

    if(running_backward){
        xVelocity += acceleration;
        if(xVelocity > maxspeed){
            xVelocity = maxspeed;
        }
        // if(x() > position){
        //     setPos(x() - xVelocity, y());
        // }
        // else {
        //     emit scrollWorldRight(xVelocity);
        // }
        setPos(x() - xVelocity, y());
        //emit moveLeftWithPlayer();
        }
    else if(!running_backward && !running_forward){
        xVelocity -= acceleration;
        if(xVelocity < 0){
            xVelocity = 0;
        }
         setPos(x() - xVelocity, y());
    }
        emit CenterOnPlayer();
}

bool Player::hitObstacle()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    for(auto item : collisions){
        Obstacle * obstacle = dynamic_cast<Obstacle *>(item);
        enemy * e = dynamic_cast<enemy *>(item);
        if(obstacle || e){
            return true;
        }
    }
    return false;
}

void Player::damage()
{
    if(hitObstacle() || pos().y() > 460){
        //emit reduceLife();
        lives -= 1;
        if(lives == 0){
            emit restartLevel();
        }
        else
        {
                emit restartFromCheckpoint();
        }
    }
}

void Player::hitCheckpoint()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    for(auto item : collisions){
        checkpoint * cp= dynamic_cast<checkpoint *>(item);
        if(cp){
            lastcheckpoint = cp->pos();
            lastcheckpoint.setY(lastcheckpoint.y() - 160);
        }
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

