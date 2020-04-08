#include "StateMachine.h"

StateMachine::StateMachine() : current_state(
        Utilities::GameState::MENU_NUM_OF_PLAYERS) {}//Game starts from choosing number of players (for now at least)

Utilities::GameState StateMachine::get_cur_state() {
    return current_state;
}

Utilities::GameState StateMachine::get_prev_state() {
    return prev_state;
}

void StateMachine::one_player_mode() {
    current_state = Utilities::GameState::PLAYER_SELECTION;
    current_mode = Utilities::GameMode::SINGLE_PLAYER;
    emit set_num_of_players(Utilities::GameMode::SINGLE_PLAYER);
}

void StateMachine::two_players_mode() {
    current_state = Utilities::GameState::PLAYER_SELECTION;
    current_mode = Utilities::GameMode::TWO_PLAYERS;
    emit set_num_of_players(Utilities::GameMode::TWO_PLAYERS);
}

void StateMachine::exit_game() {
    current_state = Utilities::GameState::EXIT;
    emit set_exit_game();
}

void StateMachine::start_level() {
    current_state = Utilities::GameState::LEVEL_ON;
    emit set_level();
}


void StateMachine::menu_mode() {
    current_state = Utilities::GameState::MENU_MODE;
    emit set_menu_mode();
}