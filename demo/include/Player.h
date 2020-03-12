#pragma once

#include "Object.h"

class Player : public Object {
private:
    bool moving;
    bool jumping;
    bool falling;
    bool dead;

    const double gr_acceleration;
    double starting_jumping_speed;
    double vert_speed;
    double hor_speed;

    QPointF previous_position;
    Object* object_on_which_moving;
public:
    Player();
    bool is_on_floor();
    void start_jumping();
    void start_falling();
    void end_jumping();
    void set_hor_speed(double new_speed);
    void virtual solve_collisions();
};
