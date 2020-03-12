#include "Player.h"
#include <QList>

Player::Player()
    : Object()
    , moving(false)
    , jumping(false)
    , falling(false)
    , dead(false)
    , gr_acceleration(10)
    , starting_jumping_speed(50)
    , vert_speed(0)
    , hor_speed(0)
    , previous_position()
    , object_on_which_moving(nullptr)
{}

bool Player::is_on_floor() {
    return (!(falling && jumping));
}

void Player::start_jumping() {
    if (falling) return;

    hor_speed = starting_jumping_speed;
}

void Player::start_falling() {
    jumping = false;
    falling = true;
}

void Player::end_jumping() {
    jumping = false;
    falling = true;
    hor_speed = 0;
}

void Player::set_hor_speed(double new_speed) {
    hor_speed = new_speed;
}

void Player::solve_collisions() {
    if (!is_collidable() || dead) return;

    bool revert = false; // if needed to go to prev_pos
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (auto &item : colliding_items){
        auto *obj = dynamic_cast<Object *> (item);

        if (!obj) continue;

        if(!obj->is_collidable()) continue;

        if (dynamic_cast<Player *>(obj)) continue;

        Direction collision_dir = collision_direction(obj);

        if (collision_dir == Direction::UNKNOWN) continue; // if it is not possible to calculate it,  we skip current collision

        // case 1: touching an object while falling

        if (collision_dir == Direction::DOWN && falling){
            falling = false;
            object_on_which_moving = obj;
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



