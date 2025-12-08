#include "level.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

void level::restartLevel() {

    // Delete every item except player
    for(auto item : items()) {
        if(item != player) {
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

    player->setLives(3);
    player->setPos(30, 200);
    player->xVelocity = 0;
    player->yVelocity = 0;

    loadLevel2();
}

void level::goToLevel2(){
    // Delete every item except player
    for(auto item : items()) {
        if(item != player) {
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

    player->setLives(3);
    player->setPos(30, 200);
    player->xVelocity = 0;
    player->yVelocity = 0;

    loadLevel2();
}

void level::goToLevel3(){
    // Delete every item except player
    for(auto item : items()) {
        if(item != player) {
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

    player->setLives(3);
    player->setPos(30, 200);
    player->xVelocity = 0;
    player->yVelocity = 0;

    loadLevel3();
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
     timer = new QTimer(this);

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

    // === GROUND (Full floor for safety) ===
    for(int i = 0; i < 100; i++){
        Block *dirt = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        dirt->setPos(-30 + i*70, 400);
        dirt->setScale(1.5);
        addItem(dirt);
        blocks.append(dirt);
    }

    // === SECTION 1: Tutorial Jump (Easy) ===
    // Low platform - closer to ground
    for(int i = 0; i < 4; i++){
        Block *platform1 = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        platform1->setPos(300 + (i * 70), 340);  // Changed from 320 to 340 (closer to ground)
        platform1->setScale(1.5);
        addItem(platform1);
        blocks.append(platform1);
    }

    // === SECTION 2: Coin Collection Tutorial ===
    // Ground-level coins (easy to collect)
    for(int i = 0; i < 3; i++){
        Coin* coin = new Coin(nullptr, i);
        coin->setPos(600 + i*100, 330);  // Changed from 300 to 330 (lower)
        addItem(coin);
        coins.append(coin);
        connect(coin, &Coin::taken, this, [this](){ emit coinTaken(1); });
    }

    // === SECTION 3: Platform Jumping Tutorial ===
    // Gentle staircase of platforms
    for(int i = 0; i < 3; i++){
        Block *stair = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        stair->setPos(950 + (i * 80), 350 - (i * 25));  // Changed from 320-(i*40) to 350-(i*25) - more gradual
        stair->setScale(1.5);
        addItem(stair);
        blocks.append(stair);
    }

    // Reward coin at top of stairs - not too high
    Coin* stairCoin = new Coin(nullptr, 0);
    stairCoin->setPos(1100, 270);  // Changed from 200 to 270 (much lower)
    addItem(stairCoin);
    coins.append(stairCoin);
    connect(stairCoin, &Coin::taken, this, [this](){ emit coinTaken(1); });

    // === CHECKPOINT 1 (After Tutorial) ===
    checkpoint * cp1 = new checkpoint(nullptr, 1300, 330, false);  // Changed from 300 to 330 (closer to ground)
    cp1->setScale(0.1);
    cps.append(cp1);
    addItem(cp1);

    // === SECTION 4: First Obstacle (Single Spike) ===
    QList<QPixmap> spikeFrame;
    spikeFrame.append(QPixmap(":/assets/Spike.png"));
    Obstacle * spike1 = new Obstacle(spikeFrame, 100, nullptr);
    spike1->setPos(1500, 350);
    spike1->setScale(0.65);
    spike1->setZValue(-1);
    obstacles.append(spike1);
    addItem(spike1);

    // Platform to jump over spike - lower height
    for(int i = 0; i < 2; i++){
        Block *safePlatform = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        safePlatform->setPos(1450 + (i * 70), 320);  // Changed from 280 to 320 (lower)
        safePlatform->setScale(1.5);
        addItem(safePlatform);
        blocks.append(safePlatform);
    }

    // === SECTION 5: Gap Jump ===
    // Platform before gap
    for(int i = 0; i < 3; i++){
        Block *preGap = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        preGap->setPos(1750 + (i * 70), 340);  // Changed from 320 to 340 (closer to ground)
        preGap->setScale(1.5);
        addItem(preGap);
        blocks.append(preGap);
    }

    // Gap (no blocks)

    // Platform after gap with reward
    for(int i = 0; i < 4; i++){
        Block *postGap = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        postGap->setPos(2100 + (i * 70), 340);  // Changed from 320 to 340 (closer to ground)
        postGap->setScale(1.5);
        addItem(postGap);
        blocks.append(postGap);
    }

    // Reward coins after gap
    for(int i = 0; i < 2; i++){
        Coin* gapCoin = new Coin(nullptr, i);
        gapCoin->setPos(2150 + i*100, 290);  // Changed from 250 to 290 (lower)
        addItem(gapCoin);
        coins.append(gapCoin);
        connect(gapCoin, &Coin::taken, this, [this](){ emit coinTaken(1); });
    }

    // === SECTION 6: First Enemy ===
    enemy *enemy1 = new enemy(nullptr, 2450, 300);  // Changed from 250 to 300
    enemy1->setBlocks(blocks);
    enemy1->setBounds(2400, 2700);  // Patrol range
    addItem(enemy1);
    enemies.append(enemy1);

    // Safe platform to observe enemy
    for(int i = 0; i < 3; i++){
        Block *observePlatform = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        observePlatform->setPos(2550 + (i * 70), 320);  // Changed from 280 to 320 (lower)
        observePlatform->setScale(1.5);
        addItem(observePlatform);
        blocks.append(observePlatform);
    }

    // === SECTION 7: Multiple Obstacles ===
    // Two spikes with safe path
    for(int i = 0; i < 2; i++){
        Obstacle * spike = new Obstacle(spikeFrame, 100, nullptr);
        spike->setPos(2850 + i*200, 350);
        spike->setScale(0.65);
        spike->setZValue(-1);
        obstacles.append(spike);
        addItem(spike);
    }

    // Platforms to navigate spikes - lower
    for(int i = 0; i < 2; i++){
        Block *navPlatform = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        navPlatform->setPos(2900 + (i * 70), 320);  // Changed from 280 to 320 (lower)
        navPlatform->setScale(1.5);
        addItem(navPlatform);
        blocks.append(navPlatform);
    }

    for(int i = 0; i < 2; i++){
        Block *navPlatform2 = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        navPlatform2->setPos(3100 + (i * 70), 320);  // Changed from 280 to 320 (lower)
        navPlatform2->setScale(1.5);
        addItem(navPlatform2);
        blocks.append(navPlatform2);
    }

    // === CHECKPOINT 2 (Before Final Challenge) ===
    checkpoint * cp2 = new checkpoint(nullptr, 3300, 330, false);  // Changed from 300 to 330
    cp2->setScale(0.1);
    cps.append(cp2);
    addItem(cp2);

    // === SECTION 8: Final Challenge - Moving Obstacle ===
    QList<QPixmap> moFrames;
    moFrames.append(QPixmap(":/assets/Ratating_Spike_8.png"));
    MovingObject* mo = new MovingObject(timer, 3500, 3900, moFrames);
    mo->setPos(3500, 380);
    mo->setZValue(-1);
    addItem(mo);

    // Platform path around moving obstacle
    for(int i = 0; i < 2; i++){
        Block *finalPlatform = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        finalPlatform->setPos(3600 + (i * 70), 300);  // Changed from 250 to 300 (lower)
        finalPlatform->setScale(1.5);
        addItem(finalPlatform);
        blocks.append(finalPlatform);
    }

    // Victory coins - lower and more accessible
    for(int i = 0; i < 5; i++){
        Coin* victoryCoin = new Coin(nullptr, i);
        victoryCoin->setPos(3850 + i*60, 280 - i*15);  // Changed from 200-i*20 to 280-i*15 (lower, less steep)
        addItem(victoryCoin);
        coins.append(victoryCoin);
        connect(victoryCoin, &Coin::taken, this, [this](){ emit coinTaken(1); });
    }

    // if (!player->scene()) {  // only add if not already in a scene
    //     addItem(player);
    // }
    // player->setZValue(1);

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

    connect(timer, &QTimer::timeout, player, &Player::fall);
    connect(timer, &QTimer::timeout, player, &Player::hitCheckpoint);
    connect(timer, &QTimer::timeout, player, &Player::damage);
    connect(timer, &QTimer::timeout, this, &level::reduceLife);
    connect(timer, &QTimer::timeout, this, &level::updateLives);

    connect(player, &Player::restartLevel, this, &level::restartLevel);
    connect(player, &Player::restartFromCheckpoint, this, &level::restartFromCheckpoint);
    connect(this, &level::coinTaken, score, &Score::increase);
    timer->start(16);
}

void level::loadLevel3()
{
    // Background and Scene setup

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

    for(int i = 0; i < 40; i++){
        Block *dirt = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        dirt->setPos(-30 + i*70, 400);
        dirt->setScale(1.5); addItem(dirt); blocks.append(dirt);
        while(i*70 > 1000 && i*70 < 2000){
            i++;
        }
    }
    for(int i = 0; i < 3; i++){
        Block *platform3 = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        platform3->setPos(-30 + 200 + 1000 + (i * 70), 330);
        platform3->setScale(1.5); addItem(platform3);
        blocks.append(platform3);
    }
    for(int i = 0; i < 3; i++){
        Block *platform3 = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        platform3->setPos(1200 + 200 + (i * 70), 270);
        platform3->setScale(1.5); addItem(platform3); blocks.append(platform3);
    }
    for(int i = 0; i < 3; i++){
        Block *platform3 = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        platform3->setPos(1450 + 200 + (i * 70), 210);
        platform3->setScale(1.5); addItem(platform3);
        blocks.append(platform3);
    }
    for(int i = 0; i < 3; i++){
        Block *platform3 = new Block(QPixmap(":/assets/Dirt_Block.png"), nullptr);
        platform3->setPos(1700 + 200 + (i * 70), 300);
        platform3->setScale(1.5);
        addItem(platform3);
        blocks.append(platform3);
    }

    //addItem(player);
    //player->setPos(30, 200);
    //player->setZValue(1);

    // if (!player->scene()) {  // only add if not already in a scene
    //     addItem(player);
    // }
    // player->setZValue(1);

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

    connect(coin1, &Coin::taken, this, [this](){emit coinTaken(1);});

    Coin* coin2 = new Coin(nullptr, 1);
    coin2->setPos(600, 250);

    addItem(coin2);
    coins.append(coin2);

    connect(coin2, &Coin::taken, this, [this](){emit coinTaken(1);});


    checkpoint * cp2 = new checkpoint(nullptr, 1610 + 200, 165, false);
    cp2->setScale(0.1);
    cps.append(cp2);
    addItem(cp2);

    checkpoint * cp3 = new checkpoint(nullptr, 2600, 360, true);
    cp3->setScale(0.1);
    cps.append(cp3);
    addItem(cp3);

    //score
    score = new Score();
    score->setZValue(3);
    addItem(score);

    connect(player, &Player::restartLevel, this, &level::restartLevel);
    connect(player, &Player::restartFromCheckpoint, this, &level::restartFromCheckpoint);
    connect(player, &Player::goToLevel2, this, &level::goToLevel2);
    connect(this, &level::coinTaken, score, &Score::increase);

    // if(timer) {
    //     timer->stop();
    //     timer->disconnect();
    //     delete timer;
    // }

    timer = new QTimer(this);

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
    connect(player, &Player::restartFromCheckpoint, this, &level::reduceLife); //added instead of timeout
    connect(timer, &QTimer::timeout, this, &level::updateLives);
    timer->start(16);
}

level::level(QObject *parent, int number, Player* p) : QGraphicsScene(parent), player(p)
{
    setSceneRect(0, 0, 1080 * 5, 500);

    if(number == 1) loadLevel1();
    else if(number == 2) loadLevel2();

    //nextLevelTimer = new QTimer(this);
    //connect(nextLevelTimer, &QTimer::timeout, this, &level::NextLevel);
    //nextLevelTimer->start(16);
}

void level::loadLevel2()
{
    timer = new QTimer(this);

    for(int i = 0; i < 5; i ++){
        QGraphicsPixmapItem *Background_layer1 = new QGraphicsPixmapItem(QPixmap(":/assets/3 Background/Day/Background.png"));

        Background_layer1->setScale(1.7);
        Background_layer1->setX(i*900);
        Background_layer1->setZValue(-3);
        addItem(Background_layer1);
    }

    Block *dirt = new Block(QPixmap(":/assets/1 Tiles/BayTile_05.png"), nullptr, 470);
    dirt->setPos(30, 400);
    dirt->setScale(1);
    addItem(dirt);
    blocks.append(dirt);
    for(int i = 0; i < 40; i++){
        Block *dirt = new Block(QPixmap(":/assets/1 Tiles/BayTile_06.png"), nullptr, 470);
        dirt->setPos(50 + i*30, 400);
        dirt->setScale(1);
        addItem(dirt);
        blocks.append(dirt);
    }
    for(int i = 0; i < 2; i ++){
        Block * block = new Block(QPixmap(":/assets/1 Tiles/BayTile_19.png"), nullptr, 470);
        block->setPos(300 + i*400, 370);
        block->setScale(1);
        addItem(block);
        blocks.append(block);
    }

    Block * block2 = new Block(QPixmap(":/assets/1 Tiles/BayTile_10.png"), nullptr, 470);
    block2->setPos(1250 , 400);
    block2->setScale(1);
    addItem(block2);
    blocks.append(block2);

    Block *block4 = new Block(QPixmap(":/assets/1 Tiles/BayTile_05.png"), nullptr, 470);
    block4->setPos(1400, 400);
    dirt->setScale(1);
    addItem(block4);
    blocks.append(block4);

    for(int i = 0; i < 40; i++){
        Block *dirt = new Block(QPixmap(":/assets/1 Tiles/BayTile_06.png"), nullptr, 470);
        dirt->setPos(1430 + i*30, 400);
        dirt->setScale(1);
        addItem(dirt);
        blocks.append(dirt);
    }

    Block * block5 = new Block(QPixmap(":/assets/1 Tiles/BayTile_10.png"), nullptr, 470);
    block5->setPos(2630 , 400);
    block5->setScale(1);
    addItem(block5);
    blocks.append(block5);

    for(int i = 0; i < 2; i++){
        QList<QPixmap> frame;
        frame.append(QPixmap(":/assets/FS1.png"));
        Obstacle * obs = new Obstacle(frame, 100, nullptr);
        obs->setPos(1500 + i*200, 370);
        obs->setScale(0.5);
        obstacles.append(obs);
        addItem(obs);
    }

    for(int i = 0; i < 2; i++){
        QList<QPixmap> frame;
        frame.append(QPixmap(":/assets/FS1.png"));
        Obstacle * obs = new Obstacle(frame, 100, nullptr);
        obs->setPos(2000 + i*200, 370);
        obs->setScale(0.5);
        obstacles.append(obs);
        addItem(obs);
    }

    QList<QPixmap> frame1;
    frame1.append(QPixmap(":/assets/UDS.png"));
    Obstacle * uds = new Obstacle(frame1, 100, nullptr);
    uds->setPos(1600, 230);
    uds->setScale(0.5);
    obstacles.append(uds);
    addItem(uds);

    QList<QPixmap> frame;
    frame.append(QPixmap(":/assets/LemonGrap.png"));
    MovingObject * mo = new MovingObject(timer,330,670,frame,100,nullptr );
    mo->setPos(400, 323);
    mo->setScale(0.27);
    obstacles.append(mo);
    addItem(mo);

    QList<QPixmap> frame3;
    frame3.append(QPixmap(":/assets/RS1.png"));
    MovingObject * RS1 = new MovingObject(timer,2000,2300,frame3,100,nullptr );
    RS1->setPos(2000, 300);
    RS1->setScale(0.27);
    obstacles.append(RS1);
    addItem(RS1);

    //final flag
    checkpoint * final = new checkpoint(nullptr, 2600, 320, true);
    final->setScale(0.1);
    cps.append(final);
    addItem(final);

    // player->setpos(30,300);
    // player->setZValue(1);

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

    connect(timer, &QTimer::timeout, player, &Player::fall);
    connect(timer, &QTimer::timeout, player, &Player::hitCheckpoint);
    connect(timer, &QTimer::timeout, player, &Player::damage);
    connect(timer, &QTimer::timeout, this, &level::reduceLife);
    connect(timer, &QTimer::timeout, this, &level::updateLives);

    connect(player, &Player::restartLevel, this, &level::restartLevel);
    connect(player, &Player::restartFromCheckpoint, this, &level::restartFromCheckpoint);
    connect(this, &level::coinTaken, score, &Score::increase);
    connect(player, &Player::goToLevel3, this, &level::goToLevel3);
    timer->start(16);
}

void level::NextLevel(){
    if(player->currentLevel == 2){
        goToLevel2();
    }
}

void level::clearLevel()
{
    for (auto item : items()) {
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

    player->setLives(3);
    player->setPos(30, 200);
    player->setLastcheckpoint(QPointF(30, 200));
    player->setZValue(1);


    player->xVelocity = 0;
    player->yVelocity = 0;
}

level::~level()
{
    for (auto item : items()) {
        if(item != player) {
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
}


void level::reduceLife()
{
    if (!lives.isEmpty() && lives.size() > player->getLives()) {
        delete lives.last();
        lives.pop_back();
    }

    // Check if player has run out of lives (not if lives list is empty)
    if (player->getLives() <= 0) {
        qDebug() << "Player lives reached 0, emitting gameOver";
        emit gameOver();
    }
}

void level::addPlayer(Player* p) {
    if (!p) {
        qDebug() << "addPlayer called with null pointer!";
        return;
    }

    if (p->scene() && p->scene() != this) {
        p->scene()->removeItem(p);
    }

    player = p;
    if (!player->scene()) addItem(player);
    player->setPos(30, 200);
}

void level::cleanup() {
    if (timer) {
        timer->stop();
        timer->disconnect();
    }

    for (auto item : items()) {
        if (item != player) {
            removeItem(item);
            delete item;  // safe now, timer is disconnected
        }
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


