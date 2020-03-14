#pragma once

#include "Object.h"
#include <QObject>
#include <QGraphicsItem>
#include "Block.h"

class Player : public Object {
public:
    bool moving;
    bool jumping;
    bool falling;
    bool dead;

    const double gr_acceleration;
    const double starting_jumping_speed;
    const double starting_falling_speed;
    double vert_speed;
    double hor_speed;
    const double width;
    const double height;

    Direction direction;

    void check_floor();
    int color;
    int m_direction;
    QPointF previous_position;
    Block *object_on_which_moving;
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
