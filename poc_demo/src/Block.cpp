#include "Block.h"

Block::Block(QPoint position, const QString &file_name) {
    setPixmap(QPixmap(file_name).scaled(block_width, block_height));
    setPos(position);
}