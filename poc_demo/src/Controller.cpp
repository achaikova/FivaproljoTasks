#pragma once

#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include "Controller.hpp"

Controller::Controller(Player *player, QWidget *parent)
	: QWidget(parent)
	, player(player)
{}

void Controller::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_D and !event->isAutoRepeat()) {
		player->set_direction(RIGHT);
		player->set_moving(true);
		qDebug() << "D pressed!";
	} else if (event->key() == Qt::Key_A and !event->isAutoRepeat()) {
		player->set_direction(LEFT);
		player->set_moving(true);
		qDebug() << "A pressed!";
	} else if (event->key() == Qt::Key_W and !event->isAutoRepeat()) {
		player->set_direction(UP); //??? А если по диагонаи или это вообще не тут надо ставить но допустим
		player->set_jumping(true);
}

void Controller::keyReleaseEvent(QKeyEvent *event) {
	player->set_direction(UNKNOWN);
	if (event->key() == Qt::Key_W) {
		player->set_jumping(false);
	} else if (event->key() == Qt::Key_A or event->key() == Qt::Key_D) {
		player->set_moving(false);
	}
}
