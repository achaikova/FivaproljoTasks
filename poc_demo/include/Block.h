#ifndef DEMO_BLOCK_H
#define DEMO_BLOCK_H

#include <QGraphicsPixmapItem>

class Block : public QGraphicsPixmapItem {
public:
    Block(QPoint position, const QString &name, int w, int h);
};

#endif //DEMO_BLOCK_H
