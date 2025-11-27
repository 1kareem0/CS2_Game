#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include "player.h"
#include "block.h"
#include <QTimer>

class Game : public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene * scene;
    Player * player;
    QList<Block*> blocks;
    QGraphicsPixmapItem* currentBackground;  // Changed: single background instead of list
public:
    Game(QWidget* parent = nullptr);

public slots:
    void scrollWorld(int speed);
};

#endif // GAME_H
