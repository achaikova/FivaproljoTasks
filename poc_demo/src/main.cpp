#include <iostream>
#include <QApplication>
#include "Scene.h"
#include "Model.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *model = new Model();
    return a.exec();
}