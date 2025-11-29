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

public slots:
};

#endif // GAME_H
