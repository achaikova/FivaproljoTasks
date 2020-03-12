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

class Scene : public QGraphicsView {
public:
    Scene(QWidget *parent = 0);

    void add_background(QString image);

    void add_platform(int x, int y, int amount, QString image);

    void add_player(Player *player);

    QGraphicsScene *game_scene;
private:
    QImage *background;


};

#endif //DEMO_SCENE_H
