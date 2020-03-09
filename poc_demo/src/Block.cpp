#include "Block.h"

Block::Block(QPoint position) {
    setPixmap(QPixmap("../images/black_block.png").scaled(72, 72));
    setPos(position);
}
