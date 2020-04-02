#include "Player.h"
#include <QApplication>
#include <include/LevelStatistics.h>
#include "Model.h"
#include <QSplashScreen>
#include <QMainWindow>
#include "Controller.h"
#include "LevelStatisticsTest.h"

//for now game is started by calling run_game -> later that will be called from MENU
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *ctrl = new Controller();
   // auto *ctrl = new Controller();
    ctrl->run_game(); // пока демка и вообще должно с меню запускаться
    return a.exec();
}
