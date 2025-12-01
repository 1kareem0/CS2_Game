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

class level : public QGraphicsScene
{
public:
    Player * player;
    QList<Block*> blocks;
    QList<Obstacle *> obstacles;
    QList<enemy*> enemies;
    std::vector<Life *> lives;

public slots:
    void restartLevel();
    void restartFromCheckpoint();
    void scrollWorldLeft(int speed);
    void scrollWorldRight(int speed);
    void reduceLife();

public:
    level(QObject *parent = nullptr, int number  =1);
    void loadLevel1();
    bool isCheckpoint();
};

#endif // LEVEL_H
