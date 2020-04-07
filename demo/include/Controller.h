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

class Controller : public QObject {
Q_OBJECT
public:
    Controller(int argc, char *argv[]);

    //~Controller() override; TODO - clean mess

    int runGame(); // later - change name to start/begin

private slots:

    void one_player_level();

    void two_player_level();

    void exit_game();

    //void end_level();

    void run_level();

signals:

    void set_run_level();

private:
    Application app;
    QTimer *level_durance = nullptr;
    Model *model_ = nullptr;
    Scene *scene_ = nullptr;
    KeyPresser *key_presser_ = nullptr;
    StateMachine *state_machine_ = nullptr;
    Menu *menu_ = nullptr;
    KeyPresserHelper *key_presser_helper_ = nullptr;
    std::vector<Player *> players_;
};
