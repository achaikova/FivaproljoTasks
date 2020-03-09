#include "Block.h"


Block::Block (QPoint point){
    setPixmap(QPixmap("../images/platform.png"));
    setPos(100, 100);
}
