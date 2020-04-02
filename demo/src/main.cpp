#include "Player.h"
#include <QApplication>
#include <include/LevelStatistics.h>
#include "Model.h"
#include "Controller.h"
#include "LevelStatisticsTest.h"

bool is_test = false; // case we test or not

void test(){
    // LevelStatisticsTest tests //

    LevelStatisticsTest test_statistics;
    test_statistics.run_all_tests();
    LevelStatisticsTest::show_final_result();

    // Place for any other tests //
    //            ...           //
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // Если не тестируем - запускаем игру
    if (!is_test){
        auto *ctrl = new Controller();
        ctrl->run_game();
        return a.exec();
    }
    // Запуск тестов
    test();
    return a.exec();
}
