#include "Model.h"
#include "Player.h"
#include <QTimer>


Model::Model(Scene *scene, StateMachine *state_machine) : game_scene(scene), state_machine(state_machine) {
    game_just_ended = false;
    game_on = true;
    engine = new QTimer(this);
    QObject::connect(engine, SIGNAL(timeout()), this, SLOT(advance_scene()));
    engine->start(10);
    engine->setInterval(10);
}


void Model::make_new_level() { //TODO - find other way to load game
    game_scene->add_background("images/background.jpg");
    QString default_block = "images/1block.jpg";
    int block_size = ceil((double) game_scene->get_width() / 25.0);
    //1st platform
    game_scene->add_platform(400, 150, 9, default_block, block_size);
    // 2nd platform
    game_scene->add_platform(150, 250, 3, default_block, block_size);
    // and so on
    game_scene->add_platform(300, 300, 3, default_block, block_size);
    game_scene->add_platform(150, 480, 4, default_block, block_size);
    game_scene->add_platform(500, 530, 1, default_block, block_size);
    game_scene->add_platform(550, 480, 1, default_block, block_size);
    game_scene->add_platform(600, 430, 1, default_block, block_size);
    game_scene->add_platform(650, 480, 1, default_block, block_size);
    game_scene->add_platform(700, 530, 1, default_block, block_size);
    game_scene->add_platform(1250 - 150 - 200, 480, 4, default_block, block_size);
    game_scene->add_platform(1250 - 150 - 150, 250, 3, default_block, block_size);
    game_scene->add_platform(1250 - 300 - 150, 300, 3, default_block, block_size);
    //add floor
    game_scene->add_platform(0, game_scene->get_height() - block_size, 25, default_block, block_size);
    //add ceiling
    game_scene->add_platform(0, 0, 25, default_block, block_size);
    //add left wall
    for (int i = 0; i < 12; i++) {
        game_scene->add_platform(0, block_size + i * block_size, 1, default_block, block_size);
    }
    //add right wall
    for (int i = 0; i < 12; i++) {
        game_scene->add_platform(game_scene->get_width() - block_size, block_size + i * block_size, 1, default_block,
                                 block_size);
    }
    game_scene->add_players(players_);
    game_scene->show();
}

void Model::advance_scene() {
    if (!game_on) {
        return;
    }
    advance_players();
}

void Model::stop_advance_scene() {
    engine->stop();
    game_on = false;
    qDebug() << "STOP";
}

void Model::advance_players() {
    for (auto player : players_) {
        player->previous_position = player->pos();
        if (player->moving) {
            if (player->direction == Utilities::Direction::LEFT) {
                player->setX(player->x() - player->hor_speed);
                if (!player->jumping and !player->falling) {
                    player->check_floor();
                }
            } else if (player->direction == Utilities::Direction::RIGHT) {
                player->setX(player->x() + player->hor_speed);
                if (!player->jumping and !player->falling) {
                    player->check_floor();
                }
            }
            solve_collisions(player);
        }

        if (player->jumping) {
            player->setY(player->y() - player->vert_speed);
            solve_collisions(player);
        }

        if (player->falling) {
            player->setY(player->y() + player->hor_speed);
            solve_collisions(player);
        }
    }
}

void Model::solve_collisions(Player *player) {
    bool revert = false;

    for (QGraphicsItem *item: player->collidingItems()) {

        if (Block *platform = dynamic_cast<Block *>(item)) {

            lvl_statistic->change_block_color(platform, player);
            platform->change_color(player->color);

            Utilities::Direction collision_dir = player->collision_direction(platform);
            if (collision_dir == Utilities::Direction::UNKNOWN) continue;
            if (collision_dir == Utilities::Direction::DOWN && player->falling) {
                player->object_on_which_moving = platform;
                player->stop_falling();
            }
            // case 2: touching an object while jumping
            if (collision_dir == Utilities::Direction::UP && player->jumping) {
                player->stop_jumping();
            }

            revert = true; // if we got here we need to go back

        }
    }

    if (revert) {
        player->setPos(player->previous_position);
    }
}

void Model::add_players(std::vector<Player *> &players) {
    players_ = players;
    for (auto player : players_) {
        player->set_size(game_scene->get_width() / 25, game_scene->get_width() / 25 + 10);
    }
}

void Model::set_statistics() {
    lvl_statistic = new LevelStatistics(players_, game_scene, state_machine);
}

void Model::show_statistics() {
    lvl_statistic->run_level_statistic();
}
