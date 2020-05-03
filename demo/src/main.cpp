#include "Player.h"
#include <QApplication>
#include "Model.h"
#include "Controller.h"
#include "Application.h"

int main(int argc, char *argv[]) {
    auto *ctrl = new Controller(argc, argv);
    ctrl->run_game();
}
