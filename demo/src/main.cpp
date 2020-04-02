#include "Player.h"
#include <QApplication>
#include <include/LevelStatistics.h>
#include "Model.h"
#include "Controller.h"
#include "LevelStatisticsTest.h"

bool is_test = false; // case we test or not

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if (!is_test){
        auto *ctrl = new Controller();
        ctrl->runGame();
        return a.exec();
    }

    LevelStatisticsTest test_statistics;
    test_statistics.run_all_tests();
    LevelStatisticsTest::show_final_result();
    return a.exec();
}
