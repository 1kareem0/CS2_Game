#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include "player.h"
#include "block.h"
#include "enemy.h"
#include <QTimer>
#include <QObject>
class Game : public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene * scene;
    QGraphicsView * view;
    Player * player;
    QList<enemy*> enemies;
    QList<Block*> blocks;
    QGraphicsPixmapItem * Background_layer1;
    QGraphicsPixmapItem * Background_layer2;
    QGraphicsPixmapItem * Background_layer3;

    //for showing the number of remaining lives.
    QGraphicsTextItem *livesText;
public:
    Game(QWidget* parent = nullptr);

    void restartLevel();
    void updateLivesDisplay();
    void showGameOver();

public slots:
    void scrollWorldLeft(int speed);
    void scrollWorldRight(int speed);
    void onPlayerDied();
    void onGameOver();
};

#endif // GAME_H
