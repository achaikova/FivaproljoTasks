#include <vector>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include "Controller.h"

// is controller responsible for menu?
// for now - yes

void Controller::run_game() { // is responsible for menu
    run_game_match();
}

void Controller::load_player(Player player, Utilities::Color color, QString name_of_image) {
    player.cutomize_player(color, name_of_image);
}

void Controller::end_game() {
    model_->print_statistics();
    assert(false);
}

void Controller::run_game_match() {
    //number of players and their customization should be received from keys/mouse - how?
    //for now default - two players
    //also key presser should be initialized in run_game and without players - i trust Egor with that
    players_.push_back(new Player(Utilities::Color::GREEN, "images/demo_player.png"));
    players_.push_back(new Player(Utilities::Color::RED, "images/demo_player.png"));
    model_ = new Model();
    model_->add_players(players_);
    scene_ = new Scene();
    key_presser_ = new KeyPresser(players_[0], players_[1]);
    key_presser_->setFixedSize(QSize(scene_->scene()->width(), scene_->scene()->height()));
    scene_->addWidget(key_presser_);
    model_->make_new_level(scene_);

    // Add timer. When he is out - game is over and collected statistics is printed.
    // Игра длится 5 (!) секунд at this moment
    /* auto game_duration_timer = new QTimer(this);
     QObject::connect(game_duration_timer, SIGNAL(timeout()), this, SLOT(end_game()));
     game_duration_timer->start(5000);*/
}

