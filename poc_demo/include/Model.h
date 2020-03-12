#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <QGraphicsPixmapItem>
#include "Entity.h"
#include "Scene.h"
#include <vector>

class Model : public QObject {
    Q_OBJECT
public:
    Model();
private:
    void advance_scene();

    bool game_on;
    QVector<Entity *> players_v;
    Scene *scene;
private slots:
    void advance_players();
};

#endif //DEMO_MODEL_H
