#include "Player.h"
#include <QList>
#include <cmath>
#include "Block.h"

Player::Player()
        : color(Color::GREEN), image("images/demo_player.png") {
    setPixmap(QPixmap(image));
}

void Player::start_jumping() {
    if (falling) return;

    jumping = true;
    vert_speed = starting_jumping_speed;
}

void Player::solve_collisions() {
    //  QList<QGraphicsItem*> items =  collidingItems();

    bool revert = false;

    for (QGraphicsItem *item: collidingItems()) {

        if (auto *platform = qgraphicsitem_cast<Block *>(item)) {
            platform->change_color(color);

            Direction collision_dir = collision_direction(platform);
            if (collision_dir == Direction::UNKNOWN) continue;
            if (collision_dir == Direction::DOWN && falling) {
                object_on_which_moving = platform;
                stop_falling();
            }
            // case 2: touching an object while jumping
            if (collision_dir == Direction::UP && jumping) {
                stop_jumping();
            }

            revert = true; // if we got here we need to go back

        }
    }

    if (revert) {
        setPos(previous_position);
    }
}


QRectF Player::boundingRect() const {
    return QRectF(0, 0, 50, 60);
}

void Player::stop_jumping() {
    //assert(!falling); // potential bug
    jumping = false;
    vert_speed = 0;
    start_falling();
}

void Player::start_falling() {
    //assert(!jumping); // potential bug

    falling = true;
    vert_speed = starting_falling_speed;
}

void Player::stop_falling() {
    falling = false;
    vert_speed = 0;
}

void Player::check_floor() {
    if (x() + width < object_on_which_moving->x()
        || object_on_which_moving->x() + object_on_which_moving->get_block_width() < x()) {

        start_falling();
    }
}

void Player::change_direction() {
    if (direction != Direction::UNKNOWN) {
        QTransform transform;
        if (p_direction != direction) {
            transform.translate(50, 0).scale(-1, Qt::YAxis);
        }
        setTransform(transform);
    }
}
