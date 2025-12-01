#ifndef COIN_H
#define COIN_H

#include <QGraphicsPathItem>
#include <QObject>
#include <QGraphicsItem>

class Coin: public QObject ,public QGraphicsPixmapItem
{
    Q_OBJECT
    int value;
    double leftBound ;
    double rightBound;
public:
    Coin(QGraphicsItem* parent, int type);
    void setBounds(double left, double right);
signals:
    void taken(int v);
public slots:
    void CheckTaken();
};

#endif // COIN_H
