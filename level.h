#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QString>
#include "player.h"
#include <QDebug>
#include "MovingObject.h"
#include "block.h"
#include "enemy.h"
#include "coin.h"
#include "score.h"

class level : public QGraphicsScene
{
    Q_OBJECT

public:
    QTimer * timer;
    QTimer * nextLevelTimer;
    Player * player;
    Score * score;
    QList<Block*> blocks;
    QList<Obstacle *> obstacles;
    QList<enemy*> enemies;
    QList<checkpoint *> cps;
    QList<Coin*> coins;
    QList<Life *> lives;
    float end;

public slots:
    void restartLevel();
    void restartFromCheckpoint();
    void reduceLife();
    void goToLevel2();
    void goToLevel3();
    //void NexLevel();

signals:
    void CenterOnPlayer();
    void coinTaken(int amount);
    void gameOver();

public:
    level(QObject* parent, int number, Player* p);
    void loadLevel1();
    bool isCheckpoint();
    void updateLives();
    void loadLevel2();
    void loadLevel3();
    void clearLevel();
    void cleanup();

    ~ level();
    void addPlayer(Player *p);
    void NextLevel();
};

#endif // LEVEL_H
