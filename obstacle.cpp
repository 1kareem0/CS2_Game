#include "obstacle.h"
#include "obstacle.h"

Obstacle::Obstacle(const QList<QPixmap> &frames, int frameInterval, QGraphicsItem *parent)
    : frames(frames)
{
    currentFrame = 0;

    if (!frames.isEmpty()) {
        setPixmap(frames[0]);  // Show first frame
    }

    for (const auto &pix : frames) {
        if (pix.width() > maxWidth) maxWidth = pix.width();
        if (pix.height() > maxHeight) maxHeight = pix.height();
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Obstacle::advanceFrame);
    timer->start(frameInterval);
}

QRectF Obstacle::boundingRect() const
{
    // Fixed rectangle so frames don't shift
    return QRectF(0, 0, maxWidth, maxHeight);
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (frames.isEmpty()) return;

    // Draw current frame centered
    const QPixmap &pix = frames[currentFrame];
    int x = (maxWidth - pix.width()) / 2;
    int y = (maxHeight - pix.height()) / 2;
    painter->drawPixmap(x, y, pix);
}

void Obstacle::advanceFrame()
{
    if (frames.isEmpty()) {
        timer->stop();
        return;
    }

    currentFrame = (currentFrame + 1) % frames.size();
    setPixmap(frames[currentFrame]);
}

Obstacle::Obstacle(const QPixmap& pixmap, QGraphicsItem* parent) : QGraphicsPixmapItem(pixmap, parent)
{
    setPixmap(QPixmap(pixmap));
}
