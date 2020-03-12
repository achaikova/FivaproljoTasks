#include "Scene.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>


Scene::Scene(QWidget *parent) {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1250, 700);
    scene->setBackgroundBrush(QBrush(QImage("images/background.jpg")));

    setScene(scene);
    setFixedSize(1250, 700);

    size_t block_width = 50;
    size_t block_height = 50;
    std::vector<Block *> floor;
    for (int i = 0; i < 25; i++) {
        floor.push_back(new Block(QPoint(0 + block_width * i, 650), "images/1block.jpg"));
        scene->addItem(floor[i]);
    }

    //meh
    //just tmp scene
    std::vector<Block *> platform_1;
    for (int i = 0; i < 9; i++) {
        platform_1.push_back(new Block(QPoint(400 + block_width * i, 150), "images/1block.jpg"));
        scene->addItem(platform_1[i]);
    }
    std::vector<Block *> platform_2;
    for (int i = 0; i < 3; i++) {
        platform_2.push_back(new Block(QPoint(150 + block_width * i, 250), "images/1block.jpg"));
        scene->addItem(platform_2[i]);
    }
    std::vector<Block *> platform_3;
    for (int i = 0; i < 3; i++) {
        platform_3.push_back(new Block(QPoint(300 + i * block_width, 300), "images/1block.jpg"));
        scene->addItem(platform_3[i]);
    }
    std::vector<Block *> platform_4;
    for (int i = 0; i < 4; i++) {
        platform_4.push_back(new Block(QPoint(150 + i * block_width, 480), "images/1block.jpg"));
        scene->addItem(platform_4[i]);
    }
    std::vector<Block *> platform_5;
    for (int i = 0; i < 3; i++) {
        platform_5.push_back(
                new Block(QPoint(500 + i * block_width, 530 - i * block_height), "images/1block.jpg"));
        scene->addItem(platform_5[i]);
    }
    for (int i = 0; i < 2; i++) {
        platform_5.push_back(
                new Block(QPoint(650 + i * block_width, 480 + i * block_height), "images/1block.jpg"));
        scene->addItem(platform_5[3 + i]);
    }
    std::vector<Block *> platform_6;
    for (int i = 0; i < 4; i++) {
        platform_6.push_back(
                new Block(QPoint(1250 - 150 - 200 + i * block_width, 480), "images/1block.jpg"));
        scene->addItem(platform_6[i]);
    }
    std::vector<Block *> platform_7;
    for (int i = 0; i < 3; i++) {
        platform_7.push_back(
                new Block(QPoint(1250 - 150 - 150 + i * block_width, 250), "images/1block.jpg"));
        scene->addItem(platform_7[i]);
    }
    std::vector<Block *> platform_8;
    for (int i = 0; i < 3; i++) {
        platform_8.push_back(
                new Block(QPoint(1250 - 300 - 150 + i * block_width, 300), "images/1block.jpg"));
        scene->addItem(platform_8[i]);
    }
    std::vector<Block *> left_wall;
    for (int i = 0; i < 13; i++) {
        left_wall.push_back(new Block(QPoint(0, i * block_height), "images/1block.jpg"));
        scene->addItem(left_wall[i]);
    }
    std::vector<Block *> right_wall;
    for (int i = 0; i < 13; i++) {
        right_wall.push_back(new Block(QPoint(1250 - block_width, i * block_height), "images/1block.jpg"));
        scene->addItem(right_wall[i]);
    }
    std::vector<Block *> ceiling;
    for (int i = 0; i < 23; i++) {
        ceiling.push_back(new Block(QPoint(50 + i * block_width, 0), "images/1block.jpg"));
        scene->addItem(ceiling[i]);
    }

    show();
}

QGraphicsScene *Scene::get_scene() {
    return scene;
}
