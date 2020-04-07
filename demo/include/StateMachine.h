#pragma once

#include <functional>
#include <QObject>
#include "Utilities.h"
#include "Scene.h"


class StateMachine : public QObject {
Q_OBJECT
public:
    StateMachine();

private slots:

    void one_player_mode();

    void two_players_mode();

    void menu_mode();

    void exit_game();

signals:

    void set_one_player();

    void set_two_players();

    void set_menu_mode();

    void set_exit_game();

private:
    Utilities::GameState current_state;
    Utilities::GameMode current_mode;
};
