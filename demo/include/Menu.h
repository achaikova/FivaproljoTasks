#pragma once

#include <vector>
#include <functional>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include "Scene.h"
#include "StateMachine.h"
#include "MenuButton.h"
#include "Utilities.h"

class Menu : public QObject {
Q_OBJECT;

public:
    Menu(Scene *scene, StateMachine *state_machine);

    ~Menu() override;

    void run_menu(Utilities::GameState state);

    void init_buttons();

    void clear_menu();

    void add_name_of_game();
private:
    Scene *scene;
    StateMachine *state_machine;
    QLabel *name_of_game;
    QPushButton *two_players;
    QPushButton *one_player;
    QPushButton *exit;
    QPushButton *paint_floor_mode;
    std::vector<QPushButton *> buttons_players;
    std::vector<QPushButton *> buttons_mode;
};

