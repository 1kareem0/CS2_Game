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
public:
    Game(QWidget* parent = nullptr);

};

#endif // GAME_H
