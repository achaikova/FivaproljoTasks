#include "Block.h"

Block::Block(QPoint position, const QString& file_name, int w, int h) {
    setPixmap(QPixmap(file_name).scaled(w, h));
    setPos(position);
}
