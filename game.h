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
public slots:
    void CenterOnPlayer();
    //void restartLevel();
    void showGameOver();
protected:
};

#endif // GAME_H
