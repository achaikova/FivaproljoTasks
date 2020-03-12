#include "Entity.h"

Entity::Entity()
        : Object()
        , moving_speed(1)
        , jump_speed(2)
        , moving_speed_dv(2)
        , direction(Direction::RIGHT)
        , moving(false)
        , dead(false)
        , dying(false)
        , jumping(false)
        , falling(false)
        , falling_speed(2)
        , previous_position()
        , death_counter(0)
        , jump_duration(30)
        , death_duration(100)
        , walkable_object(nullptr)
        {}

void Entity::start_jumping() {
    if (falling || jumping) return;

    walkable_object = nullptr;
    jumping = true;
}

void Entity::end_jumping() {
    if (!jumping) return;

    jumping = false;
    jump_counter = 0;
    falling = true;
}

void Entity::solve_collisions() {
    if (!collideable || dead) return;

    QList<QGraphicsItem *> colliding_items = collidingItems();

    bool revert = false; // if needed to go to prev_pos

    for (auto &item : colliding_items){
        auto *obj = dynamic_cast<Object*> (item);

        if (!obj) continue;

        if(!obj->is_collideable()) continue;

        if (dynamic_cast<Entity*>(obj)) continue;

        Direction collision_dir = collision_direction(obj);

        if (collision_dir == Direction::UNKNOWN) continue; // if it is not possible to calculate it,
                                                                // we skip current collision
        // case 1: touching a walkable object while falling
        if (collision_dir == Direction::DOWN && falling && obj->is_walkable()){
            falling = false;
            walkable_object = obj;
        }
        // case 2: touching an object while jumping
        if (collision_dir == Direction::UP && jumping){
            end_jumping();
        }

        revert = true; // if we got here we need to go back
    }

    if (revert){
        setPos(previous_position);
    }
}

void Entity::die() {
    if (dying || dead) return;

    dying = true;
    death_counter = 0;
    moving = false;
}


