//
// Created by daniel on 09.03.2020.
//

#ifndef DEMO_MODEL_HPP
#define DEMO_MODEL_HPP

#include "Player.hpp"
#include <QGraphicsScene>

//enum class direction {
//    left
//    right
//};

class Model {
public:
    static Player *add_player(int x, int y, int width, int height);
};


#endif //DEMO_MODEL_HPP
