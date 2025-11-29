#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsView>
#include<QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Obstacle : public  QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    QList<QPixmap> frames;
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
