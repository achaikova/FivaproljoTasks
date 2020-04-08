#include "Menu.h"

Menu::Menu(Scene *scene, StateMachine *state_machine)
        : scene_(scene), state_machine_(state_machine) {
    add_name_of_game();
    init_buttons();
}

Menu::~Menu() { //TODO
    scene_ = nullptr;
    state_machine_ = nullptr;
}


void Menu::add_name_of_game() {
    name_of_game = new QLabel;
    name_of_game->setText("Fivaproljo");
    QFont f("Arial", 30, QFont::Bold);
    name_of_game->setFont(f);
    name_of_game->setAttribute(Qt::WA_TranslucentBackground);
    name_of_game->move(QPoint(540, 200)); //TODO - set coordinates according to scene and buttons
    name_of_game->hide();
    scene_->add_text(name_of_game);
}

void Menu::run_menu(Utilities::GameState state) {
    switch (state) {
        case Utilities::GameState::MENU_NUM_OF_PLAYERS:
            scene_->add_background("images/black_color.jpg");
            name_of_game->show();
            for (auto button : buttons_players) {
                button->show();
            }
            break;
        case Utilities::GameState::MENU_MODE : //for now skip as there is only one mode and also because i'm not sure how it should look like
            scene_->add_background("images/black_color.jpg");
            for (auto button : buttons_mode) {
                button->show();
            }
            break;
    }
    scene_->show();
}

void Menu::init_buttons() {
    one_player = new QPushButton("One Player");
    one_player->setGeometry(QRect(QPoint(525, 400),
                                  QSize(200, 50)));
    buttons_players.push_back(one_player);
    connect(one_player, SIGNAL(clicked()), state_machine_, SLOT(one_player_mode()));

    two_players = new QPushButton("Two Players");
    two_players->setGeometry(QRect(QPoint(525, 470),
                                   QSize(200, 50)));
    buttons_players.push_back(two_players);
    connect(two_players, SIGNAL(released()), state_machine_, SLOT(two_players_mode()));

    exit = new QPushButton("Exit");
    exit->setGeometry(QRect(QPoint(525, 540),
                            QSize(200, 50)));
    buttons_players.push_back(exit);
    connect(exit, SIGNAL(clicked()), state_machine_, SLOT(exit_game()));

    scene_->add_button(one_player);
    scene_->add_button(two_players);
    scene_->add_button(exit);
}

void Menu::clear_menu() {
    name_of_game->hide();
    for (auto button : buttons_players) {
        button->hide();
    }
}
