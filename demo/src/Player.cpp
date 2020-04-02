#include "Player.h"
#include <QList>
#include "Block.h"

Player::Player()
        : color(Utilities::Color::GREEN), image("images/demo_player.png") {
    setPixmap(QPixmap(image));
}

void Player::start_jumping() {
    if (falling) return;

    jumping = true;
    vert_speed = starting_jumping_speed;
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
    if (direction != Utilities::Direction::UNKNOWN) {
        QTransform transform;
        if (p_direction != direction) {
            transform.translate(50, 0).scale(-1, Qt::YAxis);
        }
        setTransform(transform);
    }
}
