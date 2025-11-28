#ifndef OBSTACLE_H
#define OBSTACLE_H



#include "block.h"
#include <QTimer>

class Obstacle : public  Block
{
    Q_OBJECT
    QList<QPixmap> frames;   // store animation frames
    int currentFrame = 0;
    int maxWidth = 0;
    int maxHeight = 0;
    QTimer* timer;

public:
    Obstacle(const QList<QPixmap> &frames, int frameInterval = 100, QGraphicsItem* parent = nullptr);
    Obstacle(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    //function for the animation
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void advanceFrame();
};

#endif // OBSTACLE_H
