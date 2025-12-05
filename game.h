#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "level.h"

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    level * currentLevel;
    Score *score;
    QGraphicsTextItem *gameOverText = nullptr;
    QGraphicsTextItem *restartText  = nullptr;

public:
    Game(QWidget* parent = nullptr);

    void restartLevel();
    void updateLivesDisplay();
    void showGameOver();
    void clearGameOver();
public slots:
    void CenterOnPlayer();
    // void moveRightWithPlayer(Life * life);
    // void moveLeftWithPlayer(Life * life);
protected:
    void keyPressEvent(QKeyEvent *event) override; //this is overriden from Qgraphicsitem
};

#endif // GAME_H
