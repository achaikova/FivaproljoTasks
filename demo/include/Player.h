#pragma once

#include "Object.h"
#include <QObject>
#include <QGraphicsItem>

class Player : public Object {
private:
    bool moving;
    bool jumping;
    bool falling;
    bool dead;

    const double gr_acceleration;
    double starting_jumping_speed;
    double vert_speed;
    int hor_speed;

    int color;
    int m_direction;
    QPointF previous_position;
    Object *object_on_which_moving;
    QString image;
public:
    Player();

    bool is_on_floor();

    bool is_moving();

    bool is_jumping();

    bool is_falling();

    void start_jumping();

    void start_falling();

    void end_jumping();

    void set_hor_speed(int new_speed);

    double get_gr_acceleration();

    double set_vert_speed(double new_speed);

    double get_hor_speed();

    double get_vert_speed();

    void virtual solve_collisions();

    int direction() const;

    void setDirection(int direction);

    QRectF boundingRect() const;

    bool is_touching_foot(QGraphicsItem *item);
};
