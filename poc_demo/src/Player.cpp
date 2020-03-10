#include "Player.h"

Player::Player()
        : Object()
        , moving_speed(1)
        , jump_speed(2)
        , moving_speed_dv(2)
        , direction(Direction::RIGHT)
        , moving(true)
        , dead(false)
        , dying(false)
        , jumping(false)
        , falling(false)
        , collectable(false)
        , falling_speed(2)
        , previous_posision()
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

void Player::advance() {

    if (!dying) {
        previous_posision = pos();
    }

    if (moving) {
        if (direction == Direction::RIGHT) {
            setX(x() + moving_speed);
        } else if (direction == Direction::LEFT) {
            setX(x() - moving_speed);
        } else if (direction == Direction::UP) {
            setY(y() - moving_speed);
        }
        solve_collisions();
    }

    if (jumping) {
        setY(y() - jump_speed);
        jump_counter += jump_speed;

        if (jump_counter > jump_duration) {
            end_jumping();
        }
        solve_collisions();
    }

    /// TO DO Interaction with walkable object; ------------------------------------------------!
    if (walkable_object) {}

    if (falling) {
        setY(y() + falling_speed);
        solve_collisions();
    }

    /// TO DO death from falling; ------------------------------------------------!
    if (0) {}

    if (dying) {
        /// TO DO animation???
        dead = true;
    }
}

void Player::solve_collisions() {
    if (!collideable || dead) return;

    /// TO DO collision solving; ------------------------------------------------!
}

void Player::die() {
    if (dying || dead) return;

    dying = true;
    death_counter = 0;
    moving = false;
}

bool Player::is_collectable() {
    return collectable;
}

bool Player::is_falling() {
    return falling;
}

bool Player::is_dead() {
    return dead;
}


