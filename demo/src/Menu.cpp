#include "Menu.h"

Menu::Menu(Scene *scene, StateMachine *state_machine)
        : scene_(scene), state_machine_(state_machine) {}

void Menu::run_menu() {
    one_player = new QPushButton("One Player");
    one_player->setGeometry(QRect(QPoint(100, 200),
                                  QSize(200, 50)));
    buttons.push_back(one_player);
    connect(one_player, SIGNAL(clicked()), state_machine_, SLOT(one_player_mode()));

    two_players = new QPushButton("Two Players");
    two_players->setGeometry(QRect(QPoint(350, 200),
                                   QSize(200, 50)));
    buttons.push_back(two_players);
    connect(two_players, SIGNAL(released()), state_machine_, SLOT(two_players_mode()));

    exit = new QPushButton("Exit");
    exit->setIconSize(exit->rect().size());
    exit->move(QPoint(600, 200));
    buttons.push_back(exit);
    connect(exit, SIGNAL(clicked()), state_machine_, SLOT(exit_game()));

    scene_->add_button(one_player);
    scene_->add_button(two_players);
    scene_->add_button(exit);
    scene_->show();
}

void Menu::clear_menu() {
    for (auto button : buttons) {
        button->hide();
    }
}
