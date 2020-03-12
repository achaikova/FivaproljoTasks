//
// Created by daniel on 09.03.2020.
//
#include "Model.h"
#include <QSize>
#include <QTimer>
#include <unistd.h>
#include <chrono>
#include <thread>


void Model::advance_players() {
    for (auto player : players_v){
        if (!player->dead) {
            player->previous_position = pos();
        }

        if (player->moving) {
            if (player->direction == Direction::RIGHT) {
                setX(x() + player->moving_speed);
            } else if (player->direction == Direction::LEFT) {
                setX(x() - player->moving_speed);
            } else if (player->direction == Direction::UP) {
                setY(y() - player->moving_speed);
            }
            player->solve_collisions();
        }

        if (player->jumping) {
            setY(y() - player->jump_speed);
            player->jump_counter += player->jump_speed;

            if (player->jump_counter > player->jump_duration) {
                player->end_jumping();
            }
            player->solve_collisions();
        }

        /// TO DO Interaction with walkable object; ------------------------------------------------!
        if (player->walkable_object) {}

        if (player->falling) {
            setY(y() + player->falling_speed);
            player->solve_collisions();
        }

        /// TO DO death from falling; ------------------------------------------------!
        if (0) {}

        if (player->dying) {
            /// TO DO animation???
            player->dead = true;
        }
    }
}

void Model::advance_scene() {
    auto *timer = new QTimer(this);
    timer->start(20);
    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (!timer->isActive()){
            QObject::connect(timer, SIGNAL(timeout()), this, SLOT(advance_players()));
            timer->start(20);
        }
        if (!game_on){
            return;
        }
    }
}

void Model::start_game() {
    //TODO get players from VIEW;
    advance_scene();
}
