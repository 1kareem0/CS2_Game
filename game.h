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
    QGraphicsView * view;
    Player * player;
    QList<Block*> blocks;
    QGraphicsPixmapItem * Background_layer1;
    QGraphicsPixmapItem * Background_layer2;
    QGraphicsPixmapItem * Background_layer3;
public:
    Game(QWidget* parent = nullptr);

public slots:
    void scrollWorldLeft(int speed);
    void scrollWorldRight(int speed);
};

#endif // GAME_H
