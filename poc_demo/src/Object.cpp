#include "Object.h"
#include <QGraphicsScene>
#include <Scene.h>


Object::Object()
    : QGraphicsPixmapItem(nullptr)
    , walkable (false)
    , collideable(true)
    {}

bool Object::is_collideable() {
    return collideable;
}

bool Object::is_walkable() {
    return walkable;
}

Direction Object::collision_direction(Object *item) {
    QRectF curr_rect = sceneBoundingRect();
    QRectF item_rect = item->sceneBoundingRect();

    if (!curr_rect.intersects(item_rect))
        return UNKNOW;
}




