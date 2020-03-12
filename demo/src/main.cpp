#include "Player.h"
#include <QApplication>
#include "Model.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *demo_level = new Model();
    return a.exec();
}
