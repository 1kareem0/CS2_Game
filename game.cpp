#include "game.h"
#include <QTimer>
#include <qlist.h>
#include "player.h"
Game::Game(QWidget *parent)
{
    scene = new QGraphicsScene();
    this->setScene(scene);

    view = new QGraphicsView(scene);
    view->setSceneRect(0, 0, 800, 600);

    scene->setSceneRect(0, 0, 1080, 500);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(1080, 500);

    // Only use background_layer_1 for Level :

    Background_layer1 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_1.png"));
    Background_layer2 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_2.png"));
    Background_layer3 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_3.png"));

    Background_layer1->setScale(3.4);
    Background_layer2->setScale(3.4);
    Background_layer3->setScale(3.4);

    Background_layer1->setZValue(-3);
    Background_layer2->setZValue(-2);
    Background_layer3->setZValue(-1);

    scene->addItem(Background_layer1);
    scene->addItem(Background_layer2);
    scene->addItem(Background_layer3);


    // Ground blocks - continuous floor
    for(int i = 0; i < 3000; i += 70){
        Block *dirt = new Block(nullptr, i);
        scene->addItem(dirt);
        blocks.append(dirt);
    }


    // floating blocks at x=1000
    for(int i = 0; i < 3; i++){
        Block *platform3 = new Block(nullptr, 1000 + (i * 70));
        platform3->setY(300);
        scene->addItem(platform3);
        blocks.append(platform3);
    }


    // Add player
    player = new Player();
    scene->addItem(player);

    // Connect scrolling
    connect(player, &Player::scrollWorldLeft, this, &Game::scrollWorldLeft);
    connect(player, &Player::scrollWorldRight, this, &Game::scrollWorldRight);

    //connecting the conditiones to teh screen.
    connect(player, &Player::playerDied, this, &Game::onPlayerDied);
    connect(player, &Player::gameOver, this, &Game::onGameOver);

    QTimer * timer = new QTimer(this);
    timer->start(16);
    connect(timer, &QTimer::timeout, player, &Player::fall);

    //The enemies part
    int enemyPositions[] = {600, 1000, 1500, 2000, 2500};

    for(int i = 0; i < 5; i++){
        enemy *e = new enemy();
        e->setPos(enemyPositions[i], 200);  // All on ground level
        scene->addItem(e);
        enemies.append(e);
    }

    //showing the number of lives on teh screen.
    livesText = new QGraphicsTextItem();
    livesText->setDefaultTextColor(Qt::white);
    livesText->setFont(QFont("Arial", 20));
    livesText->setZValue(100);  // Always on top
    scene->addItem(livesText);
    //updateLivesDisplay();

}
void Game::scrollWorldLeft(int speed)
{
    // Move all blocks
    for(Block* block : blocks){
        block->setPos(block->x() - speed, block->y());
}
}
 void Game::scrollWorldRight(int speed)
{
    for(Block* block : blocks){
        block->setPos(block->x() + speed, block->y());
    }
    for(enemy* e : enemies){
        e->setPos(e->x() + speed, e->y());
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

