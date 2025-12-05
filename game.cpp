#include "game.h"
#include <QTimer>
#include <QList>
#include <QGraphicsProxyWidget>
#include <QWidget>
Game::Game(QWidget *parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(1080, 500);

    currentLevel = new level(nullptr, 1);
    this->setScene(currentLevel);

    score = new Score();
    this->scene()->addItem(score);
    score->setZValue(1000);

    QTimer * timer = new QTimer(this);
    timer->start(16);
    Game::CenterOnPlayer();
    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    connect(currentLevel, &level::CenterOnPlayer, this, &Game::CenterOnPlayer);

    connect(currentLevel, &level::coinTaken, score, &Score::increase);
    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    //connect(timer, &QTimer::timeout, this, Game::CenterOnPlayer());
    this->setAlignment(Qt::AlignCenter);

}

void Game::CenterOnPlayer()
{
    this->centerOn(currentLevel->player);
    if (score)
    {
        int margin = 20;
        int x = this->width() - score->boundingRect().width() - margin;
        int y = margin;

        score->setPos(mapToScene(x, y));
    }
}

void Game::showGameOver()
{
    qDebug() << "Showing Game Over screen";
    //we need to add ui for teh game over
}

// void Game::moveRightWithPlayer(Life * life)
// {
//     if(currentLevel->player->pos().x() > 200){
//         life->setXVelocity(life->getXVelocity() + life->getAcceleration());
//         if(life->getXVelocity() > life->getMaxspeed()){
//             life->setXVelocity(life->getMaxspeed());
//         }
//         life->setPos(x() + life->getXVelocity(), y());
//     }
//     else life->setXVelocity(0);
// }

// void Game::moveLeftWithPlayer(Life * life){
//     if(currentLevel->player->pos().x() < 200){
//         life->setXVelocity(life->getXVelocity() + life->getAcceleration());
//         if(life->getXVelocity() > life->getMaxspeed()){
//             life->setXVelocity(life->getMaxspeed());
//         }
//         life->setPos(x() - life->getXVelocity(), y());
//     }
//     else life->setXVelocity(0);
// }


