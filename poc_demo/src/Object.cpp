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
        return Direction::UNKNOWN;

    QRectF rect_interaction = curr_rect.intersected(item_rect);
    // Interaction is vertical
    // --> collision is horizontal
    if(rect_interaction.width() < rect_interaction.height())
    {
        // left side of IR coincides with left side of current rectangle
        if(rect_interaction.left() == curr_rect.x())
            return Direction::LEFT;
        else
            return Direction::RIGHT;
    }
        // intersection rectangle is horizontal
        // --> collision is vertical
    else
    {
        // top side of IR coincides with top side of current rectangle
        if(rect_interaction.top() == curr_rect.y())
            return Direction::UP;
        else
            return Direction::DOWN;
    }
}




