#include "level.h"
#include <QGraphicsPixmapItem>

level::level(QObject *parent, int number) : QGraphicsScene(parent)
{
    // Set the scene rect here for the level object itself
    // Based on the 3000 width used for block creation
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

    // Use inherited addItem()
    addItem(Background_layer1);
    addItem(Background_layer2);
    addItem(Background_layer3);

    for(int i = 0; i < 3000; i += 70){
        Block *dirt = new Block(nullptr, i);
        addItem(dirt);
        blocks.append(dirt);
    }

    for(int i = 0; i < 3; i++){
        Block *platform3 = new Block(nullptr, 1000 + (i * 70));
        platform3->setY(300);
        addItem(platform3);
        blocks.append(platform3);
    }

    // Add player (Moved from Game)
    player = new Player();

    player->setPos(30, 300);

    player->setBlocks(blocks);
    addItem(player);

    QTimer * timer = new QTimer(this);
    timer->start(16);

    connect(timer, &QTimer::timeout, player, &Player::fall);

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

    //it is not working
    for(enemy *e : enemies){
        connect(e, &enemy::hitPlayer, this, [this, e](){
            qDebug() << "Enemy hit player!";
            player->loseLife();
        });

        connect(e, &enemy::enemyDestroyed, this, [this, e](){
            qDebug() << "Enemy destroyed!";
            enemies.removeOne(e);
        });
    }
}
