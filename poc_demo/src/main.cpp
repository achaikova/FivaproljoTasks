#include <iostream>
#include <QApplication>
#include "scene.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Scene *game_scene = new Scene();
    game_scene->show();
    return a.exec(); //я патау
}