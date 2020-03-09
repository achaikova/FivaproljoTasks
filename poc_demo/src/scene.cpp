#include "scene.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>


Scene::Scene(QWidget *parent) {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1000, 600);
    scene->setBackgroundBrush(QBrush(QImage("../images/background.jpg")));

    setScene(scene);
    setFixedSize(1000, 600);

    block_1 = new Block(QPoint(0, 0));
    scene->addItem(block_1);
    show();
}

QGraphicsScene *Scene::get_scene() {
    return scene;
}
