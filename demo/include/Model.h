#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsView>
#include "Scene.h"
#include "Player.h"
#include <vector>


class Model : public QGraphicsView {
Q_OBJECT
private:
    static Model *uniqueInstance;

    Model(QGraphicsView *parent = 0);

public:
    static Model *instance();

    //explicit Model(std::vector<Player *> &players);
    void add_players(std::vector<Player *> &players);

    void make_new_level(Scene *gs);

    void advance_players();

protected slots:

    void advance_scene();

private:
    bool game_on;
    Scene *game_scene;
    std::vector<Player *> players_;
    QTimer engine;
};

#endif //DEMO_MODEL_H
