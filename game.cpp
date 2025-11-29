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
}

// void Game::restartLevel()
// {
//     if (currentLevel) {
//         currentLevel->clear();
//         delete currentLevel;
//     }

//     currentLevel = new level(nullptr, 1);
//     this->setScene(currentLevel);

//     if (currentLevel->player) {
//         connect(currentLevel->player, &Player::scrollWorldLeft, this, &Game::scrollWorldLeft);
//         connect(currentLevel->player, &Player::scrollWorldRight, this, &Game::scrollWorldRight);
//     }
// }

void Game::showGameOver()
{
    qDebug() << "Showing Game Over screen";
    //we need to add ui for teh game over
}

