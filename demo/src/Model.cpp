#include "Model.h"
#include "Player.h"
#include <QTimer>
#include <QDebug>


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

/*Model::Model(std::vector<Player *> &players)
        : players_(players) {
}*/

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
            if (player->direction == Direction::LEFT){
                player->setX(player->x() - player->hor_speed);
                if (!player->jumping and !player->falling){
                    player->check_floor();
                }
            } else if (player->direction == Direction::RIGHT){
                player->setX(player->x() + player->hor_speed);
                if (!player->jumping and !player->falling){
                    player->check_floor();
                }
            }
            player->solve_collisions();
        }

        if (player->jumping) {
            player->setY(player->y() - player->vert_speed);
           // player->set_vert_speed(player->get_vert_speed() - player->get_gr_acceleration());
            player->solve_collisions();
            qDebug() << "Here JUMP!";
        }

        if (player->falling) {
            player->setY(player->y() + player->hor_speed);
            player->solve_collisions();
        }
    }
}

Model::Model(QWidget *parent) {
    engine = new QTimer(this);
    QObject::connect(engine, SIGNAL(timeout()), this, SLOT(advance_scene()));
    engine->start(10);
    engine->setInterval(10);
}

void Model::add_players(std::vector<Player *> &players) {
    players_ = players;
}

//Model::~Model() {}
