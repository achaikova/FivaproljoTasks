#pragma once

#include <QObject>
#include <QGraphicsItem>
#include "Block.h"
#include "Object.h"

class Player : public Object {
public:
    bool moving = false;
    bool jumping = false;
    bool falling = true;
    bool dead = false;

    int current_timer = 0;
    int timer_to_start = 45;

    const double gr_acceleration = 0.1;
    const double starting_jumping_speed = 5;
    const double starting_falling_speed = 3;
    double vert_speed = 0;
    double hor_speed = 2.5;

    Utilities::Direction direction = Utilities::Direction::UNKNOWN;
    Utilities::Direction p_direction = Utilities::Direction::RIGHT;

    Utilities::Color color;
    int m_direction = 0;
    QPointF previous_position;
    Block *object_on_which_moving = nullptr;
    QString image;
public:

    Player(Utilities::Color player_color);

    void start_jumping();

    void set_player_skin(const QString &name_of_image);

    void stop_jumping();

    void start_falling();

    void stop_falling();

    void check_floor();

    void change_skin_direction();

    QRectF boundingRect() const override;

    void set_size(int height, int width);

private:
    int height, width;
};
