#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QWidget>
#include "Scene.h"
#include "Player.h"
#include <vector>
#include "LevelStatistics.h"

class Model : public QObject {
Q_OBJECT
public:
    Model(QWidget *parent = 0);

    void add_players(std::vector<Player *> &players);

    void make_new_level(Scene *gs);

    void advance_players();

    void set_statistics();

    void solve_collisions(Player *);

    bool get_game_just_ended() {return game_just_ended;};

private slots:

    void advance_scene();

private:
    bool game_on;
    bool game_just_ended;
    Scene *game_scene;
    std::vector<Player *> players_;
    QTimer *engine;
    LevelStatistics *lvl_statistic;
};

#endif //DEMO_MODEL_H
