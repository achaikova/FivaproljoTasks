#include "scene.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>


Scene::Scene(QWidget *parent) {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1250, 700);
    scene->setBackgroundBrush(QBrush(QImage("../images/background.jpg")));

    setScene(scene);
    setFixedSize(1250, 700);


    Block *floor = new Block(QPoint(0, 650), "../images/25blocks.jpg", 1250, 50);
    scene->addItem(floor);


    //meh
    Block *platform_1 = new Block(QPoint(400, 150), "../images/9blocks.jpg", 450, 50);
    scene->addItem(platform_1);
    Block *platform_2 = new Block(QPoint(150, 250), "../images/3blocks.jpg", 150, 50);
    scene->addItem(platform_2);
    Block *platform_3 = new Block(QPoint(300, 300), "../images/3blocks.jpg", 150, 50);
    scene->addItem(platform_3);
    Block *platform_4 = new Block(QPoint(150, 480), "../images/4blocks.jpg", 200, 50);
    scene->addItem(platform_4);
    Block *platform_5 = new Block(QPoint(600, 430), "../images/1block.jpg", 50, 50);
    scene->addItem(platform_5);
    Block *platform_6 = new Block(QPoint(550, 480), "../images/1block.jpg", 50, 50);
    scene->addItem(platform_6);
    Block *platform_7 = new Block(QPoint(500, 530), "../images/1block.jpg", 50, 50);
    scene->addItem(platform_7);
    Block *platform_8 = new Block(QPoint(650, 480), "../images/1block.jpg", 50, 50);
    scene->addItem(platform_8);
    Block *platform_9 = new Block(QPoint(700, 530), "../images/1block.jpg", 50, 50);
    scene->addItem(platform_9);
    Block *platform_10 = new Block(QPoint(1250 - 150 - 200, 480), "../images/4blocks.jpg", 200, 50);
    scene->addItem(platform_10);
    Block *platform_11 = new Block(QPoint(1250 - 150 - 150, 250), "../images/3blocks.jpg", 150, 50);
    scene->addItem(platform_11);
    Block *platform_12 = new Block(QPoint(1250 - 300 - 150, 300), "../images/3blocks.jpg", 150, 50);
    scene->addItem(platform_12);


    show();
}

QGraphicsScene *Scene::get_scene() {
    return scene;
}
