#include "game.h"

Game::Game(QWidget *parent)
{
    scene = new  QGraphicsScene();
    this->setScene(scene);

    scene->setSceneRect(0, 0, 1080, 500);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(1080, 500);

    QPixmap BG_layer1(":/assets/background_layer_1.png");
    QPixmap BG_layer2(":/assets/background_layer_2.png");
    QPixmap BG_layer3(":/assets/background_layer_3.png");

    QGraphicsPixmapItem *Background_layer1 = new QGraphicsPixmapItem(BG_layer1);
    QGraphicsPixmapItem *Background_layer2 = new QGraphicsPixmapItem(BG_layer2);
    QGraphicsPixmapItem *Background_layer3 = new QGraphicsPixmapItem(BG_layer3);

    Background_layer1->setScale(3.4);
    Background_layer2->setScale(3.4);
    Background_layer3->setScale(3.4);

    Background_layer1->setZValue(-3);
    Background_layer2->setZValue(-2);
    Background_layer3->setZValue(-1);

    scene->addItem(Background_layer1);
    scene->addItem(Background_layer2);
    scene->addItem(Background_layer3);

    for(int i = 0; i < 1000; i += 70){
    Block * dirt = new Block(nullptr, i);
    scene->addItem(dirt);
    }

    player = new Player();
    scene->addItem(player);

    QTimer * timer = new QTimer(this);
    timer->start(16);
    connect(timer, &QTimer::timeout, player, &Player::fall);

}


