//
// Created by daniel on 09.03.2020.
//

#include "Object.hpp"
#include <QGraphicsScene>
#include <scene.h>


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




