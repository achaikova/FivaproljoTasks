#include <QObject>
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include "Player.hpp"

void Player::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Here!";
    if (event->key() == Qt::Key_Left) {
        if (x() <= 0){
            return;
        }
        setPos(x() - 10, y());
    }
    else if (event->key() == Qt::Key_Right){
        if (this->x() + rect().width() >= scene()->width()){
            return;
        }
        setPos(x() + 10, y());
    }
    else if (event->key() == Qt::Key_Up) {
        setPos(x(), y() - 10);
        QTimer *timer = new QTimer(this);
        timer->start(500);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(fall_down()));
        timer->start(500);

    }
}
// Создается очень много таймеров и псевдо-гравитация, придумнная мной, работает слишком хорошо.
// Остановимс на этом.
void Player::fall_down() {
    if (y() >= scene()->height() - 200){
        return;
    }
    setPos(x(), y() + 10);
}
