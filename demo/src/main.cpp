#include "Player.h"
#include <QApplication>
#include "Model.h"
#include "Controller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *ctrl = new Controller();
    ctrl->runGame();
    return a.exec();
}
