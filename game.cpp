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
    //connect(currentLevel, &level::CenterOnPlayer, this, &Game::CenterOnPlayer);

    //connect(timer, &QTimer::timeout, this, Game::CenterOnPlayer());
    connect(currentLevel, &level::gameOverTriggered, this, &Game::showGameOver);

    this->setAlignment(Qt::AlignCenter);
    this->setFocus(); //to accept the enter pressing
}

void Game::showGameOver()
{
    currentLevel->timer->stop();
    currentLevel->player->setEnabled(false);

    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("GAME OVER");
    QFont font("Arial", 48, QFont::Bold);
    gameOverText->setFont(font);
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setZValue(1000);

    gameOverText->setPos(
        currentLevel->sceneRect().width()/2 - gameOverText->boundingRect().width()/2,
        currentLevel->sceneRect().height()/2 - 100);

    currentLevel->addItem(gameOverText);

    restartText = new QGraphicsTextItem("Press ENTER to Restart");
    restartText->setFont(QFont("Arial", 20));
    restartText->setDefaultTextColor(Qt::white);
    restartText->setZValue(1000);

    restartText->setPos(
        gameOverText->x(),
        gameOverText->y() + 80);

    currentLevel->addItem(restartText);
    centerOn(currentLevel->sceneRect().center());
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

void Game::clearGameOver()
{
    if (gameOverText) { currentLevel->removeItem(gameOverText); delete gameOverText; gameOverText = nullptr; }
    if (restartText)  { currentLevel->removeItem(restartText);  delete restartText;  restartText = nullptr; }
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if (currentLevel->player->getLives() <= 0) {
            currentLevel->restartLevel();  // Restart level 1
            return;
        }
    }

    // Otherwise, pass to default behavior
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


