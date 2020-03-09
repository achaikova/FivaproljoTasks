//
// Created by daniel on 09.03.2020.
//

#ifndef DEMO_PLAYER_HPP
#define DEMO_PLAYER_HPP
#include <QGraphicsRectItem>


class Player:public QGraphicsRectItem {
public:
    Player(int scene_x, int scene_y, int width, int height);
};



#endif //DEMO_PLAYER_HPP
