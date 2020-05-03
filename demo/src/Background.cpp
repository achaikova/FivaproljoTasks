#include "Background.h"

Background::Background(const QPixmap &pixmap, QGraphicsItem *parent) : QGraphicsPixmapItem(pixmap) {}

QPainterPath Background::shape() const {
    return QPainterPath();
}
