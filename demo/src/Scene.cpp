#include "Scene.h"

Scene::Scene(QWidget *parent) {
    game_scene = new QGraphicsScene();
    game_scene->setSceneRect(0, 0, 1250, 700);
    game_scene->setBackgroundBrush(QBrush(QImage("../images/background.jpg")));

    setScene(game_scene);
    setFixedSize(1250, 700);
}

void Scene::add_background(QString image) {
    setBackgroundBrush(QBrush(QImage(image)));
}

void Scene::add_platform(int x, int y, int amount, QString image) {
    size_t block_width = 50;
    size_t block_height = 50;
    std::vector<Block *> platform;
    for (int i = 0; i < amount; i++) {
        platform.push_back(new Block(QPoint(x + block_width * i, y), image));
        game_scene->addItem(platform[i]);
    }
}

void Scene::add_player(QGraphicsPixmapItem *player) {
    return;
}

