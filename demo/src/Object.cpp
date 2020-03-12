#include "Object.h"
#include <QRectF>

Object::Object()
    : QGraphicsPixmapItem()
    , collidable (true)
{}

bool Object::is_collidable() {
    return collidable;
}

Direction Object::collision_direction(Object *item) {

    QRectF curr_rect = sceneBoundingRect();
    QRectF item_rect = item->sceneBoundingRect();

    if (!curr_rect.intersects(item_rect)){
        return Direction::UNKNOWN;
    }

    QRectF rect_interaction = curr_rect.intersected(item_rect);

    if (rect_interaction.width() < rect_interaction.height()){ // Interaction is vertical  --> collision is horizontal
        return (rect_interaction.left() == curr_rect.x()) ?  Direction::LEFT : Direction::RIGHT; // left side of IR coincides with
    }                                                                                           // left side of current rectangle
    else {                                                   // intersection rectangle is horizontal --> collision is vertical
        return (rect_interaction.top() == curr_rect.y()) ?  Direction::UP : Direction::DOWN; // top side of IR coincides
    }                                                                                       // with top side of current rectangle
}
