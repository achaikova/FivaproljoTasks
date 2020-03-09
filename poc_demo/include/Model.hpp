//
// Created by daniel on 09.03.2020.
//

#ifndef DEMO_MODEL_HPP
#define DEMO_MODEL_HPP
#include <QGraphicsPixmapItem>
#include "Player.hpp"

class Model : public QGraphicsPixmapItem{
public:
    Player* add_player(double x, double y, int width, int height);
};

#endif //DEMO_MODEL_HPP
