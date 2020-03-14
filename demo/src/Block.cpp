#include "Block.h"

Block::Block(QPoint position, const QString &file_name) {
    setPixmap(QPixmap(file_name).scaled(block_width, block_height));
    setPos(position);
}

int Block::type() const {
    return Type;
}

QRectF Block::boundingRect() const {
    return QRectF(0, 0, 50, 50);
}

void Block::add_color(int color) {
    switch (color) {
        case 1:
            setPixmap(QPixmap(QPixmap("../images/green_block.jpg")).scaled(block_width, block_height));
            break;
        default:
            break;
    }
}