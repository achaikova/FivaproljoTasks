#include "background.h"

BackgroundItem::BackgroundItem(const QPixmap &pixmap)
        : QGraphicsPixmapItem(pixmap) {}

QPainterPath BackgroundItem::shape() const {
    return QPainterPath();
}