#include <vector>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include "Controller.h"

Controller::Controller()
        : scene_(nullptr), model_(nullptr) {
}

void Controller::runGame() { // later - add loop
    players_.push_back(new Player());
    model_ = new Model();
    model_->add_players(players_);
    scene_ = new Scene();
    key_presser_ = new KeyPresser(players_[0]);
    scene_->addWidget(key_presser_);
    model_->make_new_level(scene_);
//    model_->advance_scene();
}

KeyPresser::KeyPresser(Player *player, QWidget *parent)
        : player_(player) {}

void KeyPresser::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_D and !event->isAutoRepeat()) {
        player_->set_hor_speed(1); // Right
        player_->setPos(player_->x() + 10, player_->y());
        qDebug() << "D pressed!";
    } else if (event->key() == Qt::Key_A and !event->isAutoRepeat()) {
        player_->set_hor_speed(-1); // Left
        player_->setPos(player_->x() - 10, player_->y());
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
