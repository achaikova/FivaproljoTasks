#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QWidget>
#include <QVBoxLayout>
#include "Scene.h"
#include "Player.h"
#include <vector>
#include "LevelStatistics.h"
//#include "LevelStatisticsWindow.h"

class Model : public QObject {
Q_OBJECT
public:
    Model(QWidget *parent = 0);

    void add_players(std::vector<Player *> &players);

    void make_new_level(Scene *gs);

    void advance_players();

    void set_statistics();

    void solve_collisions(Player *);

    int get_player_statistic(Player *);

    bool get_game_just_ended() { return game_just_ended; };

    void show_statistics();

private slots:

    void advance_scene();

private:
    bool game_on;
    bool game_just_ended;
    Scene *game_scene;
    std::vector<Player *> players_;
    QTimer *engine;
    LevelStatistics *lvl_statistic;
    //LevelStatisticsWindow *lvl_statistic_window;
};

#endif //DEMO_MODEL_H
