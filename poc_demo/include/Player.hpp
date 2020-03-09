//
// Created by daniel on 09.03.2020.
//

#pragma once;

#include "Object.hpp"
#include <QPointF>

class Player : public Object {
protected:
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
    bool collectable;

    int falling_speed;

    QPointF previous_posision;

    virtual void start_jumping();
    virtual void end_jumping();

    int death_counter;
    int jump_counter;
    int death_duration;
    Object *walkable_object;                    // object on which current entity is walking if any

public:
    Player();
    bool is_dead();
    bool is_falling();
    bool is_collectable();

    virtual void set_direction(Direction) = 0; /// TO DO
    virtual void set_moving(bool) = 0; /// TO DO
    virtual void advance();
    virtual void solve_collisions() override = 0; /// TO DO

    virtual std::string name()            override = 0;
    virtual void animate()                override = 0;
    virtual void hit(Object *, Direction) override = 0;

    virtual void die() = 0;
};

