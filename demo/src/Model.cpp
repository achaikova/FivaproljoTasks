#include "Model.h"
#include "Player.h"
#include <QTimer>
#include <QDebug>


void Model::make_new_level(Scene *gs) {
    game_scene = gs;
    QString default_block = "images/1block.jpg";
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
    // initialize statistic
    lvl_statistic = new LevelStatistics(players_);
    game_scene->add_player(players_[0]);
    game_scene->show();

}

void Model::advance_scene() {
    advance_players();
    if (!game_on) {
        return;
    }
}

void Model::advance_players() {
    for (auto player : players_) {
        player->previous_position = player->pos();
        if (player->moving){
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
            solve_collisions(lvl_statistic, player);
        }

        if (player->jumping) {
            player->setY(player->y() - player->vert_speed);
            solve_collisions(lvl_statistic, player);
        }

        if (player->falling) {
            player->setY(player->y() + player->hor_speed);
            solve_collisions(lvl_statistic, player);
        }
    }
}

Model::Model(QWidget *parent)
    : game_on(false) , game_scene(), players_()
    , lvl_statistic(), engine() {

    engine = new QTimer(this);
    QObject::connect(engine, SIGNAL(timeout()), this, SLOT(advance_scene()));
    engine->start(10);
    engine->setInterval(10);
}

void Model::add_players(std::vector<Player *> &players) {
    players_ = players;
}

void Model::solve_collisions(LevelStatistics *lvl_statistics, Player * player) {
    bool revert = false;

    for (QGraphicsItem *item: player->collidingItems()) {

        if (auto *platform = qgraphicsitem_cast<Block *>(item)) {

            lvl_statistics->change_block_color(platform, player);
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

void Model::print_statistics() {
    for (Player *player : players_){
        qDebug() << lvl_statistic->get_player_statistic(player);
    }
}
