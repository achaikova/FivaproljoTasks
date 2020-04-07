#pragma once

#include <QGraphicsScene>
#include <QTimer>
#include <QPushButton>
#include <QAbstractAnimation>
#include <QDebug>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Block.h"
#include "Player.h"
#include "Background.h"
#include "MenuButton.h"

class KeyPresser;

class Scene : public QGraphicsView {
public:
    Scene(QWidget *parent = 0);

    void add_background(QString image);

    void add_platform(int x, int y, int amount, QString image);

    void add_players(std::vector<Player *> players);

    // void add_button(Button *button);

    void add_button(QPushButton *button);

    void addWidget(KeyPresser *pPresser);

    //void add_item(QGraphicsItem *item);


    QGraphicsScene *game_scene;

private:
    Background *background;
};
