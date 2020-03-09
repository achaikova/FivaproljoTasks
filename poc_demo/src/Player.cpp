//
// Created by daniel on 09.03.2020.
//

#include "Player.hpp"
#include <QGraphicsScene>

Player::Player(int scene_x, int scene_y, int width, int height){
    this->setRect(scene_x, scene_y, width, height);
    scene()->addItem(this);
}

