#pragma once

#include "Object.h"
#include <QPointF>
#include <QKeyEvent> //tmp

class Player : public Object {
public:
    int moving_speed;
    int jump_speed;
    int jump_duration;
    int moving_speed_dv;

    Direction direction;
    bool moving;
    bool dead;
    bool dying;
    bool jumping;
    bool falling;

    int falling_speed;

    QPointF previous_position;

    virtual void start_jumping();

    virtual void end_jumping();

    int death_counter;
    int jump_counter;
    int death_duration;
    Object *walkable_object; // object on which current entity is walking if any


    Player();

    virtual void set_direction(Direction) = 0; /// TO DO
    virtual void set_moving(bool) = 0; /// TO DO

    void solve_collisions() override ; /// TO DO

    std::string& name() override;

    void animate() override = 0;

    void hit(Object *, Direction) override = 0;

    void die();

};

