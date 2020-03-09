//
// Created by daniel on 09.03.2020.
//

#include "Object.hpp"
#include <QGraphicsScene>

Object::Object()
    : QGraphicsPixmapItem(nullptr)
    , collideable(true)
    , walkable (false){

    scene()->addItem(this);
}
