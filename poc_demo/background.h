#ifndef DEMO_BACKGROUND_H
#define DEMO_BACKGROUND_H

#include <QGraphicsPixmapItem>

class BackgroundItem : public QGraphicsPixmapItem {
public:
    explicit BackgroundItem(const QPixmap &pixmap);

public:
    virtual QPainterPath shape() const;
};


#endif //DEMO_BACKGROUND_H
