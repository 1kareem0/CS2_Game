#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QString>
#include "player.h"
#include <QDebug>
#include "Obstacle.h"
#include "block.h"
#include "enemy.h"
#include "coin.h"
#include "score.h"

class level : public QGraphicsScene
{
    Q_OBJECT

public:
    QTimer * timer;
    Player * player;
    QList<Block*> blocks;
    QList<Obstacle *> obstacles;
    QList<enemy*> enemies;
    QList<checkpoint *> cps;
    QList<Coin*> coins;
    QList<Life *> lives;
    Score* score;


public slots:
    void restartLevel();
    void restartFromCheckpoint();
    // void scrollWorldLeft(int speed);
    // void scrollWorldRight(int speed);
    void reduceLife();

signals:
    void CenterOnPlayer();

public:
    level(QObject *parent = nullptr, int number  =1);
    void loadLevel1();
    bool isCheckpoint();
};

#endif // LEVEL_H
