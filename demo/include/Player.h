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

    const double gr_acceleration = 0.1;
    const double starting_jumping_speed = 5;
    const double starting_falling_speed = 2;
    double vert_speed = 0;
    double hor_speed = 2;
    const double width = 50;
    const double height = 60;

    Direction direction = Direction::UNKNOWN;

    void check_floor();
    BlockColor color;
    int m_direction = 0;
    QPointF previous_position;
    Block *object_on_which_moving = nullptr;
    QString image;
public:
    Player();

    void start_jumping();
    void stop_jumping();
    void start_falling();
    void stop_falling();

    void virtual solve_collisions();

    QRectF boundingRect() const override;

};
