#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>

Game::Game(QWidget *parent) :
    QGraphicsView(parent),
    currentLevel(nullptr)
{
    // Create PLAYER ONCE — global
    player = new Player(nullptr);

    // Load first level
    goToLevel(2);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1080, 500);
    setAlignment(Qt::AlignCenter);

    // Camera follow timer
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::CenterOnPlayer);
    //connect(timer, &QTimer::timeout, this, &Game::goToNextLevel);
    timer->start(16);

    // Player events handled by the Game
    connect(player, &Player::CenterOnPlayer, this, &Game::CenterOnPlayer);
    connect(player, &Player::showGameOver, this, &Game::showGameOver);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void Game::goToNextLevel(){
    if(player->getCurrentLevel() == 2){
        goToLevel(2);
    }
    else if(player->getCurrentLevel() == 3){
        //
    }
}

void Game::goToLevel(int index)
{
    // Delete old scene safely
    if (currentLevel) {
        currentLevel->cleanup();
        delete currentLevel;
    }

    // Create new level (new scene)
    currentLevel = new level(nullptr, index, player);

    // Attach scene to the view
    setScene(currentLevel);

    // Add the existing player
    currentLevel->addPlayer(player);

    // Immediately center camera
    CenterOnPlayer();
}

void Game::CenterOnPlayer()
{
    if (!currentLevel || !player) return;

    centerOn(player);

    // Keep score pinned to corner
    if (currentLevel->score)
    {
        int margin = 20;
        int x = width() - currentLevel->score->boundingRect().width() - margin;
        int y = margin;

        currentLevel->score->setPos(mapToScene(x, y));
    }
}

void Game::showGameOver()
{
    if (!currentLevel) return;

    isGameOver = true;

    if (currentLevel->timer)
        currentLevel->timer->stop();

    auto* gameOverText = new QGraphicsTextItem("GAME OVER\nPress R to Restart");

    QFont font("Arial", 30, QFont::Bold);
    gameOverText->setFont(font);
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setZValue(10);

    int sceneW = currentLevel->sceneRect().width();
    int sceneH = currentLevel->sceneRect().height();

    gameOverText->setPos(sceneW / 2 - 200, sceneH / 2 - 100);

    currentLevel->addItem(gameOverText);
}


