#include "Player.h"

Player::Player()
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
        , walkable_object(nullptr) {}

void Player::start_jumping() {
    if (falling || jumping) return;

    walkable_object = nullptr;
    jumping = true;
}

void Player::end_jumping() {
    if (!jumping) return;

    jumping = false;
    jump_counter = 0;
    falling = true;
}

void Player::solve_collisions() {
    if (!collideable || dead) return;

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (auto &item : colliding_items){
        auto *obj = dynamic_cast<Object*> (item);

        if (!obj) continue;

        if(!obj->is_collideable()) continue;

        if (dynamic_cast<Player*>(obj)) continue;

        Direction collision_dir = collision_direction(obj);
    }

    /// TO DO collision solving; ------------------------------------------------!
}

void Player::die() {
    if (dying || dead) return;

    dying = true;
    death_counter = 0;
    moving = false;
}


