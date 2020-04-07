#include "StateMachine.h"

StateMachine::StateMachine() : current_state(Utilities::GameState::INITIALIZING) {}

void StateMachine::one_player_mode() {
    current_state = Utilities::GameState::LEVEL_ON;
    current_mode = Utilities::GameMode::SINGLE_PLAYER;
    emit set_one_player();
}

void StateMachine::two_players_mode() {
    current_state = Utilities::GameState::LEVEL_ON;
    current_mode = Utilities::GameMode::TWO_PLAYERS;
    emit set_two_players();
}

void StateMachine::exit_game() {
    current_state = Utilities::GameState::EXIT;
    emit set_exit_game();
}


void StateMachine::menu_mode() {
    current_state = Utilities::GameState::MENU_MODE;
    emit set_menu_mode();
}