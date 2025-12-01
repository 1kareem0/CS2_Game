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

class level : public QGraphicsScene
{
public:
    Player * player;
    QList<Block*> blocks;
    QList<Obstacle *> obstacles;
    QList<enemy*> enemies;
    QList<Coin*> coins;

public slots:
    void restartLevel();
    void restartFromCheckpoint();
    void handlePlayerDeath();
    void scrollWorldLeft(int speed);
    void scrollWorldRight(int speed);

public:
    level(QObject *parent = nullptr, int number  =1);
    void loadLevel1();
    bool isCheckpoint();
};

#endif // LEVEL_H
