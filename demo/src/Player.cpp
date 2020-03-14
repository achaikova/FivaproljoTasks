#include "Player.h"
#include <QList>
#include <cmath>
#include "Block.h"

Player::Player()
        : Object(), moving(false), jumping(false), falling(false), dead(false), gr_acceleration(2),
          starting_jumping_speed(10), vert_speed(0), hor_speed(0), color(1), m_direction(0), previous_position(),
          object_on_which_moving(nullptr),
          image("../images/demo_player.png") {
    setPixmap(QPixmap(image));
}

bool Player::is_on_floor() {
    return (!(falling && jumping));
}

void Player::start_jumping() {
    if (falling) return;
    jumping = true;
    vert_speed = starting_jumping_speed;
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

void Player::set_hor_speed(int new_speed) {
    hor_speed += new_speed;
    setDirection(qBound(-1, hor_speed, 1));
    //  moving = true;
}

void Player::solve_collisions() {
    //  QList<QGraphicsItem*> items =  collidingItems();
    for (QGraphicsItem *item: collidingItems()) {
        if (Block *platform = qgraphicsitem_cast<Block *>(item)) {
            platform->add_color(color);
        }
    }
}

bool Player::is_moving() {
    return hor_speed != 0;
}

bool Player::is_jumping() {
    return jumping;
}

bool Player::is_falling() {
    return falling;
}

double Player::get_hor_speed() {
    return hor_speed;
}

double Player::get_vert_speed() {
    return vert_speed;
}

double Player::set_vert_speed(double new_speed) {
    vert_speed = new_speed;
}

double Player::get_gr_acceleration() {
    return gr_acceleration;
}

int Player::direction() const {
    return m_direction;
}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, 50, 60);
}

void Player::setDirection(int direction) {
    m_direction = direction;
    if (m_direction != 0) {
        QTransform transform;
        if (m_direction < 0) {
            transform.translate(50, 0).scale(-1, Qt::YAxis);
        }
        setTransform(transform);
    }
}