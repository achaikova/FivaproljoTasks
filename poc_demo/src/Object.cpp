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




