#include "KeyPresser.h"

KeyPresser::KeyPresser(Player *player, QWidget *parent)
        : player_manipulator_(player) {
    setWindowOpacity(0.0);
    setFocus();
}

KeyPresser::KeyPresser(Player *player1, Player *player2, QWidget *parent)
        : player_manipulator_(player1),
          second_player_manipulator(player2, Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right) {
    setWindowOpacity(0.0);
    setFocus();
}

void KeyPresser::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        if (player_manipulator_.is_active()) {
            player_manipulator_.press((Qt::Key) event->key()); //TODO cast
            //  qDebug() << "Pressed!";
        }
        if (second_player_manipulator.is_active()) {
            second_player_manipulator.press((Qt::Key) event->key()); //TODO cast
            qDebug() << "Pressed!";
        }
    }
}

void KeyPresser::keyReleaseEvent(QKeyEvent *event) {
    if (player_manipulator_.is_active()) {
        player_manipulator_.release((Qt::Key) event->key()); //TODO cast
    }
    if (second_player_manipulator.is_active()) {
        second_player_manipulator.release((Qt::Key) event->key()); //TODO cast
    }
}


KeyPresser::PlayerManipulator_::PlayerManipulator_(Player *player, Qt::Key up_key, Qt::Key left_key,
                                                   Qt::Key down_key, Qt::Key right_key)
        : player_(player), UP(up_key), LEFT(left_key), DOWN(down_key), RIGHT(right_key), is_active_(true) {}

KeyPresser::PlayerManipulator_::PlayerManipulator_() // TODO костылина для Насти (смотри хедер строка 24)
        : player_(nullptr), UP(Qt::Key_W), RIGHT(Qt::Key_D), LEFT(Qt::Key_A), DOWN(Qt::Key_S) {}

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
    if (k == UP) {
        UP.press();
        player_->start_jumping();
    } else if (k == LEFT) {
        LEFT.press();
        set_direction(Utilities::Direction::LEFT);
    } else if (k == RIGHT) {
        RIGHT.press();
        set_direction(Utilities::Direction::RIGHT);
    }
}

void KeyPresser::PlayerManipulator_::release(Qt::Key k) {
    if (k == UP) {
        UP.release();
    } else if (k == LEFT) {
        LEFT.release();
        if (RIGHT.is_pressed()) {
            set_direction(Utilities::Direction::RIGHT);
        } else {
            player_->moving = false;
            player_->direction = Utilities::Direction::UNKNOWN;
        }
    } else if (k == RIGHT) {
        RIGHT.release();
        if (LEFT.is_pressed()) {
            set_direction(Utilities::Direction::LEFT);
        } else {
            player_->moving = false;
            player_->direction = Utilities::Direction::UNKNOWN;
        }
    }
}

bool KeyPresser::PlayerManipulator_::is_active() const {
    return is_active_;
}

void KeyPresser::PlayerManipulator_::set_direction(Utilities::Direction new_direction) {
    player_->moving = true;
    player_->direction = new_direction;
    player_->change_direction();
}
