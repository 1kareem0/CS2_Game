#include "level.h"
#include <QGraphicsPixmapItem>

void level::restartLevel() {
    for(auto item : items()){
        Block * block = dynamic_cast<Block *>(item);
        Obstacle * obstacle = dynamic_cast<Obstacle *>(item);
        enemy * e = dynamic_cast<enemy *>(item);
        if(block || obstacle || e){
            removeItem(item);
            delete item;
        }
    }

   blocks.clear();
   obstacles.clear();
   enemies.clear();

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
    // Background and Scene setup (Moved from Game)
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
        platform3->setPos(-30 + 1000 + (i * 70), 330);
        platform3->setScale(1.5);
        addItem(platform3);
        blocks.append(platform3);
    }

    player = new Player();
    player->setPos(30, 300);
    addItem(player);

    //obstacles:
    QList<QPixmap> f;
    f.append(QPixmap(":/assets/Spikes.png"));
    Obstacle * spikes = new Obstacle(f, 100 ,nullptr);
    spikes->setPos(100, 400);
    spikes->setScale(1);
    obstacles.append(spikes);
    //addItem(spikes);

    //The enemy part
    // Enemy 1
    enemy *enemy1 = new enemy(nullptr, 500, 300);
    enemy1->setBlocks(blocks);
    enemy1->setBounds(300, 700);  // Set patrol range
    addItem(enemy1);
    enemies.append(enemy1);

    // Enemy 2
    enemy *enemy2 = new enemy(nullptr, 1200, 300);
    enemy2->setBlocks(blocks);
    enemy2->setBounds(1000, 1400);
    addItem(enemy2);
    enemies.append(enemy2);

    // Enemy 3:

    enemy *enemy3 = new enemy(nullptr, 1100, 200);
    enemy3->setBlocks(blocks);
    enemy3->setBounds(1000, 1200);  // Patrol on platform
    addItem(enemy3);
    enemies.append(enemy3);



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
        //I am not convinced with scrolling the enemies
        for(enemy* e : enemies){
            e->setPos(e->x() - speed, e->y());
            e->setBounds(e->x() - 300, e->x() + 300);
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
        //I might only keeping scrolling to the right
        for(enemy* e : enemies){
            e->setPos(e->x() + speed, e->y());
            e->setBounds(e->x() - 300, e->x() + 300);
        }
}
