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
#include <Entity.h>

class Scene : public QGraphicsView {
public:
    Scene(QWidget *parent = 0);

    //void add_item(QGraphicsItem *);

    QGraphicsScene *get_scene();

    QGraphicsScene *scene;
    //  Entity * player;

};


#endif //DEMO_SCENE_H
