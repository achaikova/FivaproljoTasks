#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <QGraphicsPixmapItem>
#include "Entity.h"
#include "Scene.h"
#include <vector>

class Model : public QObject {
//    Q_OBJECT
public:
    Model();
    ~Model() override;
private:
//    void advance_scene();

    bool game_on;
    QVector<Entity *> players_v;
    Scene *scene;
//public slots:
//    void advance_players();
};

#endif //DEMO_MODEL_H
