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

    QTimer * timer = new QTimer(this);
    timer->start(16);
    Game::CenterOnPlayer();
    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    connect(currentLevel->player, &Player::showGameOver, this, &Game::showGameOver);
    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    this->setAlignment(Qt::AlignCenter);
    connect(timer, & QTimer::timeout, this, &Game::LevelComplete);
}

void Game::LevelComplete(){
    int nextLevel = currentLevel->player->getCurrentLevel();
    if(nextLevel == 2){
        delete currentLevel;
        currentLevel = new level(nullptr, 3);
        this->setScene(currentLevel);
    }
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

void Game::showGameOver()
{
    isGameOver = true;

    if(currentLevel->timer){
        currentLevel->timer->stop();
    }

    QGraphicsTextItem *gameOverText =new QGraphicsTextItem("GAME OVER\nPress SPACE to Restart");

    QFont font("Arial", 30, QFont::Bold);
    gameOverText->setFont(font);
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setZValue(10000);

    int viewWidth = this->width();
    int viewHeight = this->height();
    gameOverText->setPos(viewWidth/2 - 200, viewHeight/2 - 100);

    currentLevel->addItem(gameOverText);
}
