//
// Created by daniel on 09.03.2020.
//

#ifndef DEMO_STAFF_HPP
#define DEMO_STAFF_HPP
#include <QPixmap>
#include <string>

enum class Direction{
    RIGHT, LEFT, UP, DOWN
};

static QPixmap loadTexture(const std::string file){
    return QPixmap(file.c_str());
}

#endif //DEMO_STAFF_HPP
