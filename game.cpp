#include "game.h"
#include <QTimer>
#include <qlist.h>

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

    QTimer * timer = new QTimer(this);
    timer->start(16);
    connect(timer, &QTimer::timeout, player, &Player::fall);
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
}
