#ifndef DEMO_BACKGROUND_H
#define DEMO_BACKGROUND_H

#include <QGraphicsPixmapItem>

class Background : public QGraphicsPixmapItem {
public:
    explicit Background(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;

private:
    QPixmap background;
};

#endif //DEMO_BACKGROUND_H
