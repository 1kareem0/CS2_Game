#include "score.h"
#include <QFont>



Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    score = 0;
    setPlainText("Score: 0");
    setDefaultTextColor(Qt::white);
    setFont(QFont("Arial", 20));
}

void Score::increase(int amount)
{
    score += amount;
    setPlainText(QString("Score: %1").arg(score));
}

void Score::reset()
{
    score = 0;
    setPlainText("Score: 0");
}

int Score::getScore()
{
    return score;
}

