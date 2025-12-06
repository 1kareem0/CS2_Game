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

    currentLevel = new level(nullptr, 2);
    this->setScene(currentLevel);

    QTimer * timer = new QTimer(this);
    timer->start(16);
    Game::CenterOnPlayer();
    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);

    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    this->setAlignment(Qt::AlignCenter);
}

void Game::CenterOnPlayer()
{
    this->centerOn(currentLevel->player);
    if (currentLevel->score)
    {
        int margin = 20;
        int x = this->width() - currentLevel->score->boundingRect().width() - margin;
        int y = margin;

        currentLevel->score->setPos(mapToScene(x, y));
    }
}

