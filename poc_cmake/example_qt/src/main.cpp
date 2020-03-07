#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QGraphicsView>
#include "Player.hpp"

const int MAP_WIDTH = 800;
const int MAP_HEIGHT = 600;

int main(int argc, char **argv) {
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene);

    Player *player = new Player();
    player->setRect(0, 0, 100, 100);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    view->show();

    QGraphicsRectItem *floor = new QGraphicsRectItem();
    floor->setRect(0, MAP_HEIGHT - 100, MAP_WIDTH, 100);
    scene->addItem(floor);

    view->setFixedSize(MAP_WIDTH, MAP_HEIGHT);
    scene->setSceneRect(0, 0, MAP_WIDTH, MAP_HEIGHT);
    player->setPos(view->width()/2, view->height() - player->rect().height() - 100);

    return a.exec();
}
