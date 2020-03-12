#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <QGraphicsPixmapItem>
#include "Scene.h"
//#include "Player.h"
#include <vector>

class Model : public QObject {
//    Q_OBJECT
public:
    Model();

    void make_new_level();

private:
//    void advance_scene();

    //  bool game_on;
    //QVector<Player *> players_v;
    Scene *game_scene;
//public slots:
//    void advance_players();
};

#endif //DEMO_MODEL_H
