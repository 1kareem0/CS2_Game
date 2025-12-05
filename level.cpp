#include "level.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

void level::restartLevel() {

    timer->stop();

    for(auto item : items()){
        Player * player = dynamic_cast<Player *>(item);
        if(!player){
            removeItem(item);
            delete item;
        }
    }

    delete timer;

    blocks.clear();
    obstacles.clear();
    enemies.clear();
    coins.clear();
    lives.clear();

    loadLevel1();
    player->setLives(3);
    player->setPos(30, 260);
    player->setLastcheckpoint(QPointF(30, 200));
    player->setZValue(1);
    player->damageCooldown = 0;

    timer->start();

}


void level::restartFromCheckpoint()
{
    player->setPos(player->lastcheckpoint);
    player->xVelocity = 0;
    player->yVelocity = 0;
    player->damageCooldown = 0;
}


void level::loadLevel1()
{
    // Background and Scene setup (Moved from Game)
    for(int i = 0; i < 5; i ++){
        QGraphicsPixmapItem *Background_layer1 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_1.png"));
        QGraphicsPixmapItem *Background_layer2 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_2.png"));
        QGraphicsPixmapItem *Background_layer3 = new QGraphicsPixmapItem(QPixmap(":/assets/background_layer_3.png"));

        Background_layer1->setScale(3.4);
        Background_layer2->setScale(3.4);
        Background_layer3->setScale(3.4);

        Background_layer1->setX(i*1088);
        Background_layer2->setX(i*1088);
        Background_layer3->setX(i*1088);

        Background_layer1->setZValue(-3);
        Background_layer2->setZValue(-2);
        Background_layer3->setZValue(-1);

        addItem(Background_layer1);
        addItem(Background_layer2);
        addItem(Background_layer3);
    }

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

    //player
    if(!player){
        player = new Player();
        player->setPos(30, 200);
        addItem(player);
    }

    //lives
    // for(int i = 0; i < 180; i += 60){
    //     Life * life = new Life(nullptr, i);
    //     lives.append(life);
    //     addItem(life);
    //     //connect(player, &Player::moveLeftWithPlayer, life, &Life::moveLeftWithPlayer());
    //     //connect(player, &Player::moveRightWithPlayer, life, &Life::moveRightWithPlayer());
    // }
    Life * life1 = new Life(nullptr, 0);
    Life * life2 = new Life(nullptr, 50);
    Life * life3 = new Life(nullptr, 100);

    lives.append(life1);
    lives.append(life2);
    lives.append(life3);

    addItem(life1);
    addItem(life2);
    addItem(life3);

    //this is to move with the player
    life1->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    life2->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    life3->setFlag(QGraphicsItem::ItemIgnoresTransformations);

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

    // connect(enemy1, &enemy::hitPlayer, this, &level::handlePlayerDeath);

    // // Enemy 2
    // enemy *enemy2 = new enemy(nullptr, 1200, 300);
    // enemy2->setBlocks(blocks);
    // enemy2->setBounds(1000, 1400);
    // addItem(enemy2);
    // enemies.append(enemy2);

    // connect(enemy2, &enemy::hitPlayer, this, &level::handlePlayerDeath);

    // // Enemy 3:

    // enemy *enemy3 = new enemy(nullptr, 1100, 200);
    // enemy3->setBlocks(blocks);
    // enemy3->setBounds(1000, 1200);  // Patrol on platform
    // addItem(enemy3);
    // enemies.append(enemy3);

    // connect(enemy3, &enemy::hitPlayer, this, &level::handlePlayerDeath);

    Coin* coin1 = new Coin(nullptr, 0);
    coin1->setPos(300, 250);

    addItem(coin1);
    coins.append(coin1);

    connect(coin1, &Coin::taken, this, [this](){
        emit coinTaken(1);});

    Coin* coin2 = new Coin(nullptr, 1);
    coin2->setPos(600, 250);

    addItem(coin2);
    coins.append(coin2);

    connect(coin2, &Coin::taken, this, [this](){
        emit coinTaken(1);});


    //checkpoints:
    checkpoint * cp1 = new checkpoint(nullptr, 500, 360);
    checkpoint * cp2 = new checkpoint(nullptr, 7000, 360);
    checkpoint * cp3 = new checkpoint(nullptr, 1000, 360);

    cp1->setScale(0.1);
    cp2->setScale(0.1);
    cp3->setScale(0.1);

    cps.append(cp1);
    cps.append(cp2);
    cps.append(cp3);

    addItem(cp1);
    addItem(cp2);
    addItem(cp3);

    //score
    score = new Score();
    score->setZValue(3);
    addItem(score);

    connect(player, &Player::restartLevel, this, &level::restartLevel);
    connect(player, &Player::restartFromCheckpoint, this, &level::restartFromCheckpoint);
    connect(this, &level::coinTaken, score, &Score::increase);
    //connect(player, &Player::reduceLife, this, &level::reduceLife);
    // connect(player, &Player::scrollWorldLeft, this,  &level::scrollWorldLeft);
    // connect(player, &Player::scrollWorldRight, this, &level::scrollWorldRight);

    timer = new QTimer(this);
    timer->start(16);

    //connect(timer, &QTimer::timeout, this, &level::update);
}

level::level(QObject *parent, int number): QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, 1080*5, 500);

    if(number == 1){
        loadLevel1();
    }
}

void level::reduceLife()
{
    if (lives.isEmpty()) return;

    if (!lives.isEmpty() && lives.size() > player->getLives()) {
        delete lives.last();
        lives.pop_back();
        player->setLives(player->getLives() - 1); //i added this
    }
    if (player->getLives() <= 0) {
        emit gameOverTriggered();  // New signal we will create
    }
}

void level::updateLives()
{
    int baseX = player->x() - 270;

    if(player->x() > 300){
        for (int i = 0; i < lives.size(); i++) {
            lives[i]->setPos(baseX + i * 50, 10);
        }
    }
}
