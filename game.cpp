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

    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    this->setAlignment(Qt::AlignCenter);

    connect(currentLevel, &level::gameOver, this, &Game::showGameOver);

    //functions for checking press
    this->setFocus();
    this->setFocusPolicy(Qt::StrongFocus);
}


void Game::CenterOnPlayer(){
    this->centerOn(currentLevel->player);
    if (currentLevel->score)
    {
        int margin = 20;
        int x = this->width() - currentLevel->score->boundingRect().width() - margin;
        int y = margin;
        currentLevel->score->setPos(mapToScene(x, y));
    }
}

void Game::restartLevel()
{
    isGameOver = false;

    if(currentLevel){
        this->scene()->clear();
        delete currentLevel;
        currentLevel = nullptr;
    }
    currentLevel = new level(nullptr, 1);
    currentLevel->player->setLives(3);

    this->setScene(currentLevel);
    connect(currentLevel->player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    connect(currentLevel, &level::gameOver, this, &Game::showGameOver);

    CenterOnPlayer();
}

void Game::showGameOver()
{
    isGameOver = true;

    if(currentLevel->timer){
        currentLevel->timer->stop();
    }

    QGraphicsTextItem *gameOverText =
        new QGraphicsTextItem("GAME OVER\nPress SPACE to Restart");

    QFont font("Arial", 30, QFont::Bold);
    gameOverText->setFont(font);
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setZValue(10);

    int viewWidth = this->width();
    int viewHeight = this->height();
    gameOverText->setPos(viewWidth/2 - 200, viewHeight/2 - 100);

    currentLevel->addItem(gameOverText);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(isGameOver)
    {
        if(event->key() == Qt::Key_Space)
            restartLevel();

        return; // IGNORE ALL OTHER KEYS
    }

    // Normal controls
    QGraphicsView::keyPressEvent(event);
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
