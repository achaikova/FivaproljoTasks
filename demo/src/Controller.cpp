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
          key_presser_helper_(new KeyPresserHelper(key_presser_)), player_selection(new PlayerSelection()) {

    /* key_presser_->add_menu(menu_);
    state_machine_->set_function(this->get_run_level());
    state_machine_->set_function(menu_helper_->get_run_menu());
    state_machine_->set_activate(key_presser_helper_->get_activate());
    state_machine_->set_deactivate(key_presser_helper_->get_deactivate());*/

    key_presser_->setFixedSize(QSize(scene_->scene()->width(), scene_->scene()->height()));
    scene_->addWidget(key_presser_);
    connect(state_machine_, &StateMachine::set_num_of_players, this, &Controller::set_num_of_players_for_lvl);
    connect(state_machine_, &StateMachine::set_exit_game, this, &Controller::exit_game);
    connect(player_selection, &PlayerSelection::start_level, state_machine_, &StateMachine::start_level);
    connect(state_machine_, &StateMachine::set_level, this, &Controller::run_level);
}

Controller::~Controller() {
    player_selection->~PlayerSelection();
    //TODO KeyPresser dstrctor
    menu_->~Menu();
    //TODO continue dtors
}

//different menus depending on state - right now only one
int Controller::runGame() {
    menu_->run_menu(state_machine_->get_cur_state());
    return app.exec();
}

void Controller::set_num_of_players_for_lvl(Utilities::GameMode mode) {
    switch (mode) {
        case Utilities::GameMode::SINGLE_PLAYER:
            players_.push_back(new Player(Utilities::Color::GREEN));
            key_presser_->add_players(players_[0]);
            break;
        case Utilities::GameMode::TWO_PLAYERS:
            players_.push_back(new Player(Utilities::Color::GREEN));
            players_.push_back(new Player(Utilities::Color::YELLOW));
            key_presser_->add_players(players_[0], players_[1]);
            break;
    }
    run_player_selection();
}

void Controller::run_player_selection() {
    scene_->hide();

    player_selection->add_players(players_);
    player_selection->run_player_selection();
}

void Controller::end_level() { //TODO - show window without crashing
    //level_durance->stop();
    //model_->show_statistics();
}

void Controller::run_level() {
    menu_->clear_menu();
    model_->add_players(players_);
    model_->set_statistics();
    model_->make_new_level(scene_);
    level_durance = new QTimer(this);
    connect(level_durance, SIGNAL(timeout()), this, SLOT(end_level()));
    level_durance->start(1000);
}

void Controller::exit_game() {
    app.quit();
}