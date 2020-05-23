#pragma  once

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QWidget>
#include <QVBoxLayout>
#include <cmath>
#include "Scene.h"
#include "Player.h"
#include <vector>
#include "LevelStatistics.h"
#include "StateMachine.h"

class Model : public QObject {
Q_OBJECT
public:
    Model(Scene *scene, StateMachine *state_machine);

    void add_players(std::vector<Player *> &players);

    void make_new_level();

    void advance_players();

    void set_statistics();

    void solve_collisions(Player *);

    bool get_game_just_ended() { return game_just_ended; };

    void show_statistics();

    void clear_level();

    void start_timer();

private slots:

    void advance_scene();

    void stop_advance_scene();

private:
    bool game_on;
    bool game_just_ended;
    bool level_made = false;
    std::vector<Block *> platform;
    Scene *game_scene;
    StateMachine *state_machine;
    std::vector<Player *> players_;
    QTimer *engine;
    LevelStatistics *lvl_statistic = nullptr;
};