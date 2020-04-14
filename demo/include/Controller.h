#pragma once

#include <vector>
#include <functional>
#include <QWidget>
#include <QtGui>
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsItem>
#include "Utilities.h"
#include "Player.h"
#include "Scene.h"
#include "Model.h"
#include "KeyPresser.h"
#include "Menu.h"
#include "StateMachine.h"
#include "Application.h"
#include "PlayerSelection.h"

class Controller : public QObject {
Q_OBJECT
public:
    Controller(int argc, char *argv[]);

    ~Controller() override; //TODO - clean mess

    int runGame(); // later - change name to start/begin

    void run_player_selection();

private slots:
//the name suggests that amount of players can be changed - for now this feature is not supported
    void set_num_of_players_for_lvl(Utilities::GameMode mode);

    void exit_game();

    void end_level();

    void run_level();

signals:

    void set_run_level();

    //void set_player_selection();

private:
    Application app;
    QTimer *level_durance = nullptr;
    Scene *scene_ = nullptr;
    Model *model_ = nullptr;
    KeyPresser *key_presser_ = nullptr;
    StateMachine *state_machine_ = nullptr;
    Menu *menu_ = nullptr;
    KeyPresserHelper *key_presser_helper_ = nullptr;
    std::vector<Player *> players_;
    PlayerSelection *player_selection = nullptr;
};
