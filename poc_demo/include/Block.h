#ifndef DEMO_BLOCK_H
#define DEMO_BLOCK_H

#include <QGraphicsPixmapItem>

class Block : public QGraphicsPixmapItem {
public:
    Block(QPoint position, const QString &name);

private:
    size_t block_width = 50;
    size_t block_height = 50;

};

#endif //DEMO_BLOCK_H