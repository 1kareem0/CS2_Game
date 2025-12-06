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

    void restartLevel();
    void updateLivesDisplay();
    void showGameOver();
public slots:
    void CenterOnPlayer();
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAME_H
