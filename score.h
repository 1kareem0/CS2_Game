#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score(QGraphicsItem* parent = nullptr);

    void increase(int amount);
    void reset();
    int getScore();

private:
    int score;
};

#endif // SCORE_H
