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

    Utilities::Direction direction = Utilities::Direction::UNKNOWN;
    Utilities::Direction p_direction = Utilities::Direction::RIGHT;

    void check_floor();

    Utilities::Color color;
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

    void change_direction();

    QRectF boundingRect() const override;

};
