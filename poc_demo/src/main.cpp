#include <iostream>
#include <QApplication>
#include "scene.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Scene *scene = new Scene();
    scene->show();
    return a.exec();
}