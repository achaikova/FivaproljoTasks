#include <vector>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include "Controller.h"

void Controller::runGame() { // later - add loop
    players_.push_back(new Player(Utilities::Color::GREEN, "images/demo_player.png"));
    players_.push_back(new Player(Utilities::Color::YELLOW, "images/demo_player.png"));
    model_ = new Model();
    model_->add_players(players_);
    scene_ = new Scene();
    key_presser_ = new KeyPresser(players_[0], players_[1]);
    key_presser_->setFixedSize(QSize(scene_->scene()->width(), scene_->scene()->height()));
    scene_->addWidget(key_presser_);
    model_->make_new_level(scene_);
}
