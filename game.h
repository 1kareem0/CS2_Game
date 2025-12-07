#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "level.h"

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    level * currentLevel;
    bool isGameOver; //flag for preventing any move

public:
    Game(QWidget* parent = nullptr);

    void updateLivesDisplay();
    void LevelComplete();
public slots:
    void CenterOnPlayer();
    void showGameOver();
};

#endif // GAME_H
