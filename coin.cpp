#include "coin.h"
#include "player.h"
#include <cmath>
#include <QString>
#include <QTimer>
using namespace std;
Coin::Coin(QGraphicsItem *parent, int type): QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/assets/Coin.gif"));
    setScale(0.1);

    QTimer* TakenChecker= new QTimer(this);
    TakenChecker->start(5);
    connect(TakenChecker,&QTimer::timeout,this, &Coin::CheckTaken);
}
void Coin::CheckTaken()
{
    QList<QGraphicsItem*> colliding_items= collidingItems();
    value = 1;
    for(auto it: as_const(colliding_items))
    {
        if(typeid(*it)==typeid(Player))
        {
            emit taken(value);
            this->deleteLater();
        }
    }
}

void Coin::setBounds(double left, double right)
{
    leftBound = left;
    rightBound = right;
}
