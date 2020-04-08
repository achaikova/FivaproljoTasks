#pragma once

#include <functional>
#include <QObject>
#include "Utilities.h"
#include "Scene.h"


class StateMachine : public QObject {
Q_OBJECT
public:
    StateMachine();

    Utilities::GameState get_cur_state();

    Utilities::GameState get_prev_state();

public slots:

    void one_player_mode();

    void two_players_mode();

    void menu_mode();

// will be called after choosing mode (choosing mode after player selection (perhaps(???) can be changed))
    void start_level();

    void exit_game();

signals:

    void set_num_of_players(Utilities::GameMode mode);

    void set_level();

    void set_menu_mode();

    void set_exit_game();

private:
    Utilities::GameState current_state;
    Utilities::GameState prev_state;
    Utilities::GameMode current_mode;
};
