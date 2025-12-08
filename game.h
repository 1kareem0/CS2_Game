#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "level.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);

    Player* player;          // global player
    level* currentLevel;     // current scene

    void goToLevel(int index);
    void CenterOnPlayer();

    void goToNextLevel();
private slots:
    void showGameOver();

private:
    bool isGameOver = false;
};


#endif // GAME_H
