#include <vector>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include "Controller.h"

Controller::Controller(int argc, char *argv[])
        : app(argc, argv), model_(new Model()), scene_(new Scene()), key_presser_(new KeyPresser()),
          state_machine_(new StateMachine()),
          menu_(new Menu(scene_, state_machine_)),
          key_presser_helper_(new KeyPresserHelper(key_presser_)) {

    /* key_presser_->add_menu(menu_);
    state_machine_->set_function(this->get_run_level());
    state_machine_->set_function(menu_helper_->get_run_menu());
    state_machine_->set_activate(key_presser_helper_->get_activate());
    state_machine_->set_deactivate(key_presser_helper_->get_deactivate());*/

    key_presser_->setFixedSize(QSize(scene_->scene()->width(), scene_->scene()->height()));
    scene_->addWidget(key_presser_);
    connect(state_machine_, SIGNAL(set_one_player()), this, SLOT(one_player_level()));
    connect(state_machine_, SIGNAL(set_two_players()), this, SLOT(two_player_level()));
    connect(state_machine_, SIGNAL(set_exit_game()), this, SLOT(exit_game()));
    connect(this, SIGNAL(set_run_level()), this, SLOT(run_level()));
}

int Controller::runGame() {
    menu_->run_menu();
    return app.exec();
}

void Controller::one_player_level() {
    players_.push_back(new Player(Utilities::Color::GREEN, "images/demo_player.png"));
    key_presser_->add_players(players_[0]);
    emit set_run_level();
}

void Controller::two_player_level() {
    players_.push_back(new Player(Utilities::Color::GREEN, "images/demo_player.png"));
    players_.push_back(new Player(Utilities::Color::YELLOW, "images/demo_player.png"));
    key_presser_->add_players(players_[0], players_[1]);
    emit set_run_level();
}

/*void Controller::end_level() { //TODO - show window without crashing
    level_durance->stop();
    model_->show_statistics();
}*/

void Controller::run_level() {
    menu_->clear_menu();
    model_->add_players(players_);
    model_->set_statistics();
    model_->make_new_level(scene_);
    level_durance = new QTimer(this);
    //connect(level_durance, SIGNAL(timeout()), this, SLOT(end_level()));
    //level_durance->start(1000);
}

void Controller::exit_game() {
    app.quit();
}