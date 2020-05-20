#include "Player.h"
#include <QList>
#include <cmath>
#include <utility>
#include "Block.h"

/*
 * for now player color is given, while skin can be chosen
 */

Player::Player(Utilities::Color player_color)
        : color(player_color) {}

void Player::start_jumping() {
    if (falling || jumping) return;

    current_timer = timer_to_start;
    jumping = true;
    vert_speed = starting_jumping_speed;
}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void Player::stop_jumping() {
    jumping = false;
    vert_speed = 0;
    start_falling();
}

void Player::start_falling() {
    falling = true;
    jumping = false;
    vert_speed = starting_falling_speed;
}

void Player::stop_falling() {
    falling = false;
    vert_speed = 0;
}

void Player::check_floor() {
    if (x() + width < object_on_which_moving->x()
        || object_on_which_moving->x() + object_on_which_moving->get_block_size() < x()) {

        start_falling();
    }
}

void Player::change_skin_direction() {
    if (direction != Utilities::Direction::UNKNOWN) {
        QTransform transform;
        if (p_direction != direction) {
            transform.translate(50, 0).scale(-1, Qt::YAxis);
        }
        setTransform(transform);
    }
}

void Player::set_player_skin(const QString &name_of_image) {
    image = name_of_image;
    setPixmap(QPixmap(image).scaled(50, 50));
}

void Player::set_size(int p_height, int p_width) {
    height = p_height;
    width = p_width;
};
