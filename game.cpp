#include "game.h"
#include <QTimer>
#include <QList>

Game::Game(QWidget *parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(1080, 500);

    currentLevel = new level(nullptr, 1);

    this->setScene(currentLevel);

    if (currentLevel->player) {
        connect(currentLevel->player, &Player::scrollWorldLeft, this, &Game::scrollWorldLeft);
        connect(currentLevel->player, &Player::scrollWorldRight, this, &Game::scrollWorldRight);
    }
}

void Game::scrollWorldLeft(int speed)
{
    if (currentLevel) {
        for(Block* block : currentLevel->blocks){
            block->setPos(block->x() - speed, block->y());
        }
    }
}

void Game::scrollWorldRight(int speed)
{
    if (currentLevel) {
        for(Block* block : currentLevel->blocks){
            block->setPos(block->x() + speed, block->y());
        }
    }
}
