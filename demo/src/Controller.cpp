#include <vector>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include "Controller.h"

Controller::Controller()
    : players_(1)
    , scene_(nullptr)
    , model_(nullptr) {
    players_[0] = new Player();
}

void Controller::runGame() { // later - add loop
    model_ = new Model(std::vector<Player *> players_);
    scene_ = new Scene();
    key_presser_ = new KeyPresser(players_[0]);
    scene_->addWidget(key_presser_);
    model_->make_new_level(scene_);
    model_->game_is_on();
}

KeyPresser::KeyPresser(Player *player, QWidget *parent)
    : player_(player)
    , QWidget(parent)
{}

void KeyPresser::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_D and !event->isAutoRepeat()) {
        player_->set_hor_speed(1); // Right
        qDebug() << "D pressed!";
	} else if (event->key() == Qt::Key_A and !event->isAutoRepeat()) {
        player_->set_hor_speed(-1); // Left
       	qDebug() << "A pressed!";
	} else if (event->key() == Qt::Key_W and !event->isAutoRepeat()) {
        player_->start_jumping();
        qDebug() << "W pressed!";
    }
}

void KeyPresser::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A or event->key() == Qt::Key_D) {
        player_->set_hor_speed(0);
    }
}
