#pragma once
#include <QGraphicsPixmapItem>
#include "Utilities.h"

class Object : public QGraphicsPixmapItem {
private:
    bool collidable;
public:
    Object();
    bool is_collidable();
    Direction collision_direction(Object *item);
};

