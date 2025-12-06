#include "level.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

void level::restartLevel() {
    for(auto item : items()){
        Player * player = dynamic_cast<Player *>(item);
        if(!player){
            removeItem(item);
            delete item;
        }
    }

    if (timer) {
        timer->stop();
        timer->disconnect();
        delete timer;
        timer = nullptr;
    }

    blocks.clear();
    obstacles.clear();
    enemies.clear();
    coins.clear();
    lives.clear();

    loadLevel1();

    player->setLives(3);
    player->setPos(30, 200);
    player->setLastcheckpoint(QPointF(30, 200));
    player->setZValue(1);
}


void level::restartFromCheckpoint()
{
    player->setPos(player->lastcheckpoint);
    player->xVelocity = 0;
    player->yVelocity = 0;
    for (int i = 0; i < lives.size(); i++) {
        lives[i]->setPos(30 + i*50, 10);
    }
}


void level::loadLevel1()
{

    for(auto item : items()) {
        if(item != player) {
            removeItem(item);
            delete item;
        }
    }
    blocks.clear();
    obstacles.clear();
    coins.clear();
    lives.clear();
    cps.clear();

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

    // Base ground blocks
    for (int i = 0; i < 40; i++) {
        int x = -30 + i * 70;
        if (x > 1000 && x < 2000) continue; // skip blocks in the gap

        Block *dirt = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        dirt->setPos(x, 400);
        dirt->setScale(1.5);
        addItem(dirt);
        blocks.append(dirt);
    }

    // Floating platforms
    struct PlatformInfo {
        int startX;
        int y;
        int count;
    };

    PlatformInfo platforms[] = {
        {200 + 1000, 330, 3},
        {1200 + 200, 270, 3},
        {1450 + 200, 210, 3},
        {1700 + 200, 300, 3}
    };

    for (auto &p : platforms) {
        for (int i = 0; i < p.count; i++) {
            Block *platform = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
            platform->setPos(p.startX + i * 70, p.y);
            platform->setScale(1.5);
            addItem(platform);
            blocks.append(platform);
        }
    }

    //player
    if(!player){
        player = new Player();
        player->setPos(30, 200);
        addItem(player);
    }

    //lives
    Life * life1 = new Life(nullptr, 0);
    Life * life2 = new Life(nullptr, 50);
    Life * life3 = new Life(nullptr, 100);

    lives.append(life1);
    lives.append(life2);
    lives.append(life3);

    addItem(life1);
    addItem(life2);
    addItem(life3);

    //obstacles:
    for(int i = 0; i < 2; i++){
        QList<QPixmap> frame;
        frame.append(QPixmap(":/assets/Spike.png"));
        Obstacle * spikes = new Obstacle(frame, 100 ,nullptr);
        spikes->setPos(300 + i*300 , 370);
        spikes->setScale(0.65);
        spikes->setZValue(-1);
        obstacles.append(spikes);
        addItem(spikes);
    }

    for(int i = 0; i < 3; i++){
        QList<QPixmap> frame;
        frame.append(QPixmap(":/assets/Spike.png"));
        Obstacle * spikes = new Obstacle(frame, 100 ,nullptr);
        spikes->setPos(1070 + 200 + i*240 , 300 - i*60);
        spikes->setScale(0.65);
        spikes->setZValue(-1);
        obstacles.append(spikes);
        addItem(spikes);
    }

    //The enemy part
    // Enemy 1
    enemy *enemy1 = new enemy(nullptr, 500, 300);
    enemy1->setBlocks(blocks);
    enemy1->setBounds(300, 700);  // Set patrol range
    //addItem(enemy1);
    enemies.append(enemy1);

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

    connect(coin2, &Coin::taken, this, [this](){emit coinTaken(1);});


    checkpoint * cp2 = new checkpoint(nullptr, 1610 + 200, 165);

    cp2->setScale(0.1);

    cps.append(cp2);

    addItem(cp2);

    //score
    score = new Score();
    score->setZValue(3);
    addItem(score);

    connect(player, &Player::restartLevel, this, &level::restartLevel);
    connect(player, &Player::restartFromCheckpoint, this, &level::restartFromCheckpoint);
    connect(this, &level::coinTaken, score, &Score::increase);

    if(timer) {
        timer->stop();
        timer->disconnect();
        delete timer;
    }

    timer = new QTimer(this);
    timer->start(16);

    //moving obstacel
    QList<QPixmap> moFrames;
    moFrames.append(QPixmap(":/assets/Ratating_Spike_8.png"));
    MovingObject* mo = new MovingObject(timer, 2200,   2500,   moFrames);

    mo->setPos(2000, 374);
    mo->setZValue(-1);
    addItem(mo);

    connect(timer, &QTimer::timeout, player, &Player::fall);
    connect(timer, &QTimer::timeout, player, &Player::hitCheckpoint);
    connect(timer, &QTimer::timeout, player, &Player::damage);
    connect(timer, &QTimer::timeout, this, &level::reduceLife);
    connect(timer, &QTimer::timeout, this, &level::updateLives);
}

level::level(QObject *parent, int number): QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, 1080*5, 500);

    if(number == 1){
        loadLevel1();
    }

}

void level::loadLevel2()
{



    //player
    if(!player){
        player = new Player();
        player->setPos(30, 200);
        addItem(player);
    }

    //lives
    Life * life1 = new Life(nullptr, 0);
    Life * life2 = new Life(nullptr, 50);
    Life * life3 = new Life(nullptr, 100);

    lives.append(life1);
    lives.append(life2);
    lives.append(life3);

    addItem(life1);
    addItem(life2);
    addItem(life3);


    //score
    score = new Score();
    score->setZValue(3);
    addItem(score);

    connect(player, &Player::restartLevel, this, &level::restartLevel);
    connect(player, &Player::restartFromCheckpoint, this, &level::restartFromCheckpoint);
    connect(this, &level::coinTaken, score, &Score::increase);

    if(timer) {
        timer->stop();
        timer->disconnect();
        delete timer;
    }

    timer = new QTimer(this);
    timer->start(16);


    connect(timer, &QTimer::timeout, player, &Player::fall);
    connect(timer, &QTimer::timeout, player, &Player::hitCheckpoint);
    connect(timer, &QTimer::timeout, player, &Player::damage);
    connect(timer, &QTimer::timeout, this, &level::reduceLife);
    connect(timer, &QTimer::timeout, this, &level::updateLives);
}

void level::reduceLife()
{
     if (lives.isEmpty()) return;

     if (!lives.isEmpty() && lives.size() > player->getLives()) {
         delete lives.last();
         lives.pop_back();
     }
}

void level::updateLives()
{
    int baseX = player->x() - 350;

    if(player->x() > 400){
    for (int i = 0; i < lives.size(); i++) {
        lives[i]->setPos(baseX + i * 50, 10);
        }
    }
}


