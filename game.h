#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "level.h"

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    level * currentLevel;

public:
    Game(QWidget* parent = nullptr);

    void restartLevel();
    void updateLivesDisplay();
    void showGameOver();

};

#endif // GAME_H
