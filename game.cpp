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

void Game::restartLevel()
{
    if (currentLevel) {
        currentLevel->clear();
        delete currentLevel;
    }

    currentLevel = new level(nullptr, 1);
    this->setScene(currentLevel);

    if (currentLevel->player) {
        connect(currentLevel->player, &Player::scrollWorldLeft, this, &Game::scrollWorldLeft);
        connect(currentLevel->player, &Player::scrollWorldRight, this, &Game::scrollWorldRight);
    }
}

void Game::updateLivesDisplay()
{
    if (currentLevel && currentLevel->player) {
        qDebug() << "Lives remaining:" << currentLevel->player->getLives();
    }
}

void Game::showGameOver()
{
    qDebug() << "Showing Game Over screen";
    //we need to add ui for teh game over
}

void Game::scrollWorldLeft(int speed)
{
    if (currentLevel) {
        for(Block* block : currentLevel->blocks){
            block->setPos(block->x() - speed, block->y());
        }
        //I am not convinced with scrolling the enemies
        for(enemy* e : currentLevel->enemies){
            e->setPos(e->x() - speed, e->y());
            e->setBounds(e->x() - 300, e->x() + 300);
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
    //I might only keeping scrolling to the right
    for(enemy* e : currentLevel->enemies){
        e->setPos(e->x() + speed, e->y());
        e->setBounds(e->x() - 300, e->x() + 300);
    }
}

void Game::onPlayerDied()
{
    qDebug() << "Player died!";
}

void Game::onGameOver()
{
    qDebug() << "Game Over";
}
