#include "Model.h"
#include "Player.h"

void Model::make_new_level(Scene *gs) {
    game_scene = gs;
    QString default_block = "../images/1block.jpg";
    //1st platform
    game_scene->add_platform(400, 150, 9, default_block);
    // 2nd platform
    game_scene->add_platform(150, 250, 3, default_block);
    // and so on
    game_scene->add_platform(300, 300, 3, default_block);
    game_scene->add_platform(150, 480, 4, default_block);
    game_scene->add_platform(500, 530, 1, default_block);
    game_scene->add_platform(550, 480, 1, default_block);
    game_scene->add_platform(600, 430, 1, default_block);
    game_scene->add_platform(650, 480, 1, default_block);
    game_scene->add_platform(700, 530, 1, default_block);
    game_scene->add_platform(1250 - 150 - 200, 480, 4, default_block);
    game_scene->add_platform(1250 - 150 - 150, 250, 3, default_block);
    game_scene->add_platform(1250 - 300 - 150, 300, 3, default_block);
    //add floor
    game_scene->add_platform(0, 650, 25, default_block);
    //add ceiling
    game_scene->add_platform(0, 0, 25, default_block);
    //add left wall
    for (int i = 0; i < 12; i++) {
        game_scene->add_platform(0, 50 + i * 50, 1, default_block);
    }
    //add right wall
    for (int i = 0; i < 12; i++) {
        game_scene->add_platform(1200, 50 + i * 50, 1, default_block);
    }
    game_scene->add_player(players_[0]);
    game_scene->show();
}

Model::Model(std::vector<Player *> &players)
        : players_(players) {}

void Model::advance_scene() {
    while (true) {
        advance_players();
        if (!game_on) {
            return;
        }
    }
}

void Model::advance_players() {
    for (auto player : players_) {
        if (player->is_moving()) {
            player->setX(player->x() + player->get_hor_speed());
            player->solve_collisions();
        }

        if (player->is_jumping()) {
            player->setY(player->y() + player->get_vert_speed());
            player->set_vert_speed(player->get_vert_speed() - player->get_gr_acceleration());
            player->solve_collisions();
        }

        if (player->is_falling()) {
            player->setY(player->y() + player->get_hor_speed());
            player->solve_collisions();
        }
    }
}

