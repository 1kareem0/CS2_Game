#include "level.h"
#include <QGraphicsPixmapItem>

void level::restartLevel() {
    for(auto item : items()){
        Block * block = dynamic_cast<Block *>(item);
        Obstacle * obstacle = dynamic_cast<Obstacle *>(item);
        if(block || obstacle){
            removeItem(item);
            delete item;
        }
    }

   blocks.clear();
   obstacles.clear();

    removeItem(player);
    delete player;

    loadLevel1();
}

void level::restartFromCheckpoint()
{
    player->setPos(player->lastcheckpoint);
    player->xVelocity = 0;
    player->yVelocity = 0;
}

level::level(QObject *parent, int number) : QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, 1080, 500);

    if(number == 1){
        loadLevel1();
    }
}

void level::loadLevel1()
{
    QGraphicsPixmapItem *dot = new QGraphicsPixmapItem(QPixmap(":/assets/Spike.png"));
    dot->setPos(30, 450);
    //addItem(dot);

    QGraphicsPixmapItem *Background_layer1 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_1.png"));
    QGraphicsPixmapItem *Background_layer2 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_2.png"));
    QGraphicsPixmapItem *Background_layer3 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_3.png"));

    Background_layer1->setScale(3.4);
    Background_layer2->setScale(3.4);
    Background_layer3->setScale(3.4);

    Background_layer1->setZValue(-3);
    Background_layer2->setZValue(-2);
    Background_layer3->setZValue(-1);

    addItem(Background_layer1);
    addItem(Background_layer2);
    addItem(Background_layer3);

    for(int i = 0; i < 3000; i += 70){
        Block *dirt = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        dirt->setPos(-30 + i, 400);
        dirt->setScale(1.5);
        addItem(dirt);
        blocks.append(dirt);
    }

    for(int i = 0; i < 3; i++){
        Block *platform3 = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        platform3->setPos(-30 + 1000 + (i * 70), 300);
        platform3->setScale(1.5);
        addItem(platform3);
        blocks.append(platform3);
    }

    player = new Player();
    player->setPos(30, 300);
    addItem(player);

    // QList<QPixmap> frames;
    // for(int i = 0; i < 8; i++){
    //     QString f = ":/assets/Rotating_Spike_" + QString::number(i+1) +".png";
    //     frames.append(QPixmap(f));
    // }

    // Obstacle * rotating_spikes = new Obstacle(frames, 100, nullptr);
    // rotating_spikes->setPos(30, 300);
    // addItem(rotating_spikes);

    // QList<QPixmap> frame;
    // frame.append(QPixmap(":/assets/Spike.png"));

    // Obstacle *spike = new Obstacle(frame, 100 ,nullptr);
    // spike->setPos(70, 300);
    // addItem(spike);

    connect(player, &Player::restartLevel, this, &level::restartLevel);
    connect(player, &Player::restartFromCheckpoint, this, &level::restartFromCheckpoint);
    connect(player, &Player::scrollWorldLeft, this,  &level::scrollWorldLeft);
    connect(player, &Player::scrollWorldRight, this, &level::scrollWorldRight);

    QTimer * timer = new QTimer(this);
    timer->start(16);

    connect(timer, &QTimer::timeout, player, &Player::fall);
    connect(timer, &QTimer::timeout, player, &Player::hitCheckpoint);
    connect(timer, &QTimer::timeout, player, &Player::damage);

}

void level::scrollWorldLeft(int speed)
{
        for(Block* block : blocks){
            block->setPos(block->x() - speed, block->y());
        }
        for(Obstacle* obstacle : obstacles){
            obstacle->setPos(obstacle->x() - speed, obstacle->y());
        }
}

void level::scrollWorldRight(int speed)
{
        for(Block* block : blocks){
            block->setPos(block->x() + speed, block->y());
        }
        for(Obstacle* obstacle : obstacles){
            obstacle->setPos(obstacle->x() + speed, obstacle->y());
        }
}


