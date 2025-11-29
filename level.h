#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QString>
#include "player.h"
#include "Obstacle.h"
#include "enemy.h"

class level : public QGraphicsScene
{
public:
    Player * player;
    QList<Block*> blocks;
    QList<enemy*> enemies;
public:
    level(QObject *parent = nullptr, int number  =1);
    void loadLevel1();
};

#endif // LEVEL_H
