#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QAbstractAnimation>
#include <QDebug>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Block.h"
#include "Player.h"
#include "Background.h"
//#include "Controller.h"

class KeyPresser;

class Scene : public QGraphicsView {
public:
    Scene(QWidget *parent = 0);

    void add_background(QString image);

    void add_platform(int x, int y, int amount, QString image);

    void add_player(Player *player);

    QGraphicsScene *game_scene;

    void addWidget(KeyPresser *pPresser);

private:
    Background *background;
};

#endif //DEMO_SCENE_H
