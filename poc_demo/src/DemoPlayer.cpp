//
// Created by Анастасия Чайкова on 12/03/2020.
//

#include "DemoPlayer.h"

DemoPlayer::DemoPlayer(QPoint position) : Entity() {
    setPixmap(QPixmap("images/demo_level_player.png"));
    setPos(position-QPoint(0, pixmap().height()));

    // Player is at a higher layer than other objects
    setZValue(3);
}

void DemoPlayer::jump()
{
    // do nothing if already jumping
    if(jumping)
        return;

    // start a jump
    start_jumping();
}