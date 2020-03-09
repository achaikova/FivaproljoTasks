//
// Created by daniel on 09.03.2020.
//

#include "Model.hpp"

Player *Model::add_player(int x, int y, int width, int height){
    Player *new_player = new Player(x, y, width, height);
    scene();
    return new_player;
}
