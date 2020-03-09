//
// Created by daniel on 09.03.2020.
//
#include "Model.hpp"
#include <QSize>

Player *Model::add_player(double x, double y, int width, int height) {
    Player *new_player = new Player();
    new_player->setPos(x, y);
    QSize size = QSize(100, 100);
    size.
}
