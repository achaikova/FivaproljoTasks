#include <vector>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include "Controller.h"

Controller::Controller()
    : QObject()
    , players_(), scene_(), model_(), key_presser_()
{}

void Controller::run_game() { // later - add loop
    players_.push_back(new Player());
    model_ = new Model();
    model_->add_players(players_);
    scene_ = new Scene();
    key_presser_ = new KeyPresser(players_[0]);
    key_presser_->setFixedSize(QSize(scene_->scene()->width(), scene_->scene()->height()));
    scene_->addWidget(key_presser_);
    model_->make_new_level(scene_);

    // Add timer. When he is out - game is over and collected statistics is printed.
    // Игра длится 5 (!) секунд at this moment
    auto game_duration_timer = new QTimer(this);
    QObject::connect(game_duration_timer, SIGNAL(timeout()), this, SLOT(end_game()));
    game_duration_timer->start(5000);
}

void Controller::end_game() {
    model_->print_statistics();
    assert(false);
}

KeyPresser::KeyPresser(Player *player, QWidget *parent)
        : player_manipulator_(player) {
    setWindowOpacity(0.0);
    setFocus();
}

void KeyPresser::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        player_manipulator_.press((Qt::Key) event->key()); //TODO cast
        qDebug() << "Pressed!";
    }
}

void KeyPresser::keyReleaseEvent(QKeyEvent *event) {
    player_manipulator_.release((Qt::Key) event->key()); //TODO cast
}

KeyPresser::PlayerManipulator_::PlayerManipulator_(Player *player)
        : player_(player), W(Qt::Key_W), D(Qt::Key_D), A(Qt::Key_A), S(Qt::Key_S) {}

KeyPresser::PlayerManipulator_::Key_::Key_(Qt::Key qt_name)
        : qt_name_(qt_name), is_pressed_(false) {}

KeyPresser::PlayerManipulator_::Key_::operator Qt::Key() const {
    return qt_name_;
}

bool KeyPresser::PlayerManipulator_::Key_::is_pressed() const {
    return is_pressed_;
}

void KeyPresser::PlayerManipulator_::Key_::press() {
    is_pressed_ = true;
}

void KeyPresser::PlayerManipulator_::Key_::release() {
    is_pressed_ = false;
}

void KeyPresser::PlayerManipulator_::press(Qt::Key k) {
    if (k == W) {
        W.press();
        player_->start_jumping();
    } else if (k == A) {
        A.press();
        player_->moving = true;
        player_->direction = Utilities::Direction::LEFT; // Left
        player_->change_direction();
    } else if (k == D) {
        D.press();
        player_->moving = true;
        player_->direction = Utilities::Direction::RIGHT; // Right
        player_->change_direction();
    }
}

void KeyPresser::PlayerManipulator_::release(Qt::Key k) {
    if (k == W) {
        W.release();
    } else if (k == A) {
        A.release();
        if (D.is_pressed()) {
            player_->moving = true;
            player_->direction = Utilities::Direction::RIGHT; // Right
            player_->change_direction();
        } else {
            player_->moving = false;
            player_->direction = Utilities::Direction::UNKNOWN;
        }
    } else if (k == D) {
        D.release();
        if (A.is_pressed()) {
            player_->moving = true;
            player_->direction = Utilities::Direction::LEFT; // Left
            player_->change_direction();
        } else {
            player_->moving = false;
            player_->direction = Utilities::Direction::UNKNOWN;
        }
    }
}
