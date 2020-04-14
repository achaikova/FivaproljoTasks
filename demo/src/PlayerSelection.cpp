#include "PlayerSelection.h"

PlayerSelection::PlayerSelection(Scene *scene) : scene(scene) {}

PlayerSelection::~PlayerSelection() {
    scene->~Scene();
}

void PlayerSelection::add_players(const std::vector<Player *> &new_players) {
    num_of_players = new_players.size();
    players = new_players;
}

/*
 * there will be slots for 4 players, if there are less actual players - other slots are empty
 * also TODO key press buttons (left,right) to choose skin
 */

void PlayerSelection::run_player_selection() {
    init_window();
    //scene->show();
}

void PlayerSelection::init_window() {
    scene->add_background("images/black_color.jpg");
    set_text();
    set_images();
    set_buttons();
}

void PlayerSelection::set_text() {
    character_selection = new QLabel();
    character_selection->setText("Character Selection");
    character_selection->move(50, 50);
    QFont cs_f("Arial", 30, QFont::Bold);
    character_selection->setFont(cs_f);
    character_selection->setAttribute(Qt::WA_TranslucentBackground);
    scene->add_text(character_selection);

    QFont pn_f("Arial", 25);
    for (int i = 0; i < MAX_NUM_OF_PLAYERS; i++) {
        player_num.push_back(new QLabel());
        if (i < num_of_players) {
            switch (i) {
                case 0:
                    player_num[i]->setText("Player 1");
                    break;
                case 1:
                    player_num[i]->setText("Player 2");
                    break;
                case 2:
                    player_num[i]->setText("Player 3");
                    break;
                case 3:
                    player_num[i]->setText("Player 4");
                    break;
            }
        } else {
            player_num[i]->setText("EMPTY SLOT");
        }
        player_num[i]->move(75 + 300 * i, 210);
        player_num[i]->setFont(pn_f);
        player_num[i]->setAttribute(Qt::WA_TranslucentBackground);
        scene->add_text(player_num[i]);
    }
}

void PlayerSelection::set_images() {
    for (int i = 0; i < num_of_players; i++) {
        player_textures.push_back(new QGraphicsPixmapItem());
        player_textures[i]->setPixmap(QPixmap(available_skins[0]).scaled(200, 200));
        player_textures_index.push_back(0);
        player_textures[i]->setPos(75 + 300 * i, 250);
        scene->add_pixmap(player_textures[i]);
    }
}

// clear everything in case number of players will change
void PlayerSelection::clear_player_selection() {
    for (auto i: player_textures) {
        i->hide();
    }
    character_selection->hide();
    for (auto i: player_num) {
        i->hide();
    }
    //players.clear();
    player_textures_index.clear();
    for (auto i : buttons_player1) {
        i->hide();
    }
    for (auto i : buttons_player2) {
        i->hide();
    }
    for (auto i : buttons_player3) {
        i->hide();
    }
    for (auto i : buttons_player4) {
        i->hide();
    }
    //scene->hide();
}

void PlayerSelection::set_buttons() {
    for (int i = 0; i < num_of_players; i++) {
        switch (i) {
            case 0:
                set_buttons_player1();
                break;
            case 1:
                set_buttons_player2();
                break;
            case 2:
                set_buttons_player3();
                break;
            case 3:
                set_buttons_player4();
                break;
        }
    }
}

void PlayerSelection::change_image(int player_number) {
    player_textures_index[player_number - 1] = (player_textures_index[player_number - 1] + 1) % available_skins.size();
    player_textures[player_number - 1]->setPixmap(
            QPixmap(available_skins[
                            player_textures_index[player_number - 1]]).
                    scaled(200, 200));
}

void PlayerSelection::increase_ready_num(int player_number) {
    if (++num_of_ready == num_of_players) {
        for (int i = 0; i < num_of_players; i++) {
            players[i]->set_player_skin(available_skins[player_textures_index[i]]);
        }
        clear_player_selection();
        emit start_level();
    } else {
        switch (player_number) {
            case 1:
                customize_player1->hide();
                ready_player1->hide();
                back_player1->show();
                break;
            case 2:
                customize_player2->hide();
                ready_player2->hide();
                back_player2->show();
                break;
            case 3:
                customize_player3->hide();
                ready_player3->hide();
                back_player3->show();
                break;
            case 4:
                customize_player4->hide();
                ready_player4->hide();
                back_player4->show();
                break;
            default:
                break;
        }
    }
}

void PlayerSelection::decrease_ready_num(int player_number) {
    --num_of_ready;
    switch (player_number) {
        case 1:
            customize_player1->show();
            ready_player1->show();
            back_player1->hide();
            break;
        case 2:
            customize_player2->show();
            ready_player2->show();
            back_player2->hide();
            break;
        case 3:
            customize_player3->show();
            ready_player3->show();
            back_player3->hide();
            break;
        case 4:
            customize_player4->show();
            ready_player4->show();
            back_player4->hide();
            break;
        default:
            break;
    }
}


void PlayerSelection::set_buttons_player1() {
    customize_player1 = new QPushButton("Customize");
    customize_player1->setGeometry(QRect(QPoint(75, 460),
                                         QSize(200, 50)));
    connect(customize_player1, &QPushButton::clicked, [=] { change_image(1); });

    ready_player1 = new QPushButton("Ready");
    ready_player1->setGeometry(QRect(QPoint(75, 520),
                                     QSize(200, 50)));
    connect(ready_player1, &QPushButton::clicked, this, [=] { increase_ready_num(1); });

    back_player1 = new QPushButton("Back");
    back_player1->setGeometry(QRect(QPoint(75, 580),
                                    QSize(200, 50)));
    connect(back_player1, &QPushButton::clicked, this, [=] { decrease_ready_num(1); });
    back_player1->hide();

    buttons_player1.push_back(customize_player1);
    buttons_player1.push_back(ready_player1);
    buttons_player1.push_back(back_player1);

    scene->add_button(customize_player1);
    scene->add_button(ready_player1);
    scene->add_button(back_player1);
}

void PlayerSelection::set_buttons_player2() {
    customize_player2 = new QPushButton("Customize");
    customize_player2->setGeometry(QRect(QPoint(375, 460),
                                         QSize(200, 50)));
    connect(customize_player2, &QPushButton::clicked, [=] { change_image(2); });

    ready_player2 = new QPushButton("Ready");
    ready_player2->setGeometry(QRect(QPoint(375, 520),
                                     QSize(200, 50)));
    connect(ready_player2, &QPushButton::clicked, [=] { increase_ready_num(2); });

    back_player2 = new QPushButton("Back");
    back_player2->setGeometry(QRect(QPoint(375, 580),
                                    QSize(200, 50)));
    connect(back_player2, &QPushButton::clicked, [=] { decrease_ready_num(2); });
    back_player2->hide();

    buttons_player2.push_back(customize_player2);
    buttons_player2.push_back(ready_player2);
    buttons_player2.push_back(back_player2);

    scene->add_button(customize_player2);
    scene->add_button(ready_player2);
    scene->add_button(back_player2);
}


void PlayerSelection::set_buttons_player3() {
    customize_player3 = new QPushButton("Customize");
    customize_player3->setGeometry(QRect(QPoint(675, 460),
                                         QSize(200, 50)));
    connect(customize_player3, &QPushButton::clicked, [=] { change_image(3); });

    ready_player3 = new QPushButton("Ready");
    ready_player3->setGeometry(QRect(QPoint(675, 520),
                                     QSize(200, 50)));
    connect(ready_player3, &QPushButton::clicked, [=] { increase_ready_num(3); });

    back_player3 = new QPushButton("Back");
    back_player3->setGeometry(QRect(QPoint(675, 580),
                                    QSize(200, 50)));
    connect(back_player3, &QPushButton::clicked, [=] { decrease_ready_num(3); });
    back_player3->hide();

    buttons_player3.push_back(customize_player3);
    buttons_player3.push_back(ready_player3);
    buttons_player3.push_back(back_player3);

    scene->add_button(customize_player3);
    scene->add_button(ready_player3);
    scene->add_button(back_player3);
}


void PlayerSelection::set_buttons_player4() {
    customize_player4 = new QPushButton("Customize");
    customize_player4->setGeometry(QRect(QPoint(975, 460),
                                         QSize(200, 50)));
    connect(customize_player4, &QPushButton::clicked, [=] { change_image(4); });

    ready_player4 = new QPushButton("Ready");
    ready_player4->setGeometry(QRect(QPoint(975, 520),
                                     QSize(200, 50)));
    connect(ready_player4, &QPushButton::clicked, [=] { increase_ready_num(4); });

    back_player4 = new QPushButton("Back");
    back_player4->setGeometry(QRect(QPoint(975, 580),
                                    QSize(200, 50)));
    connect(back_player4, &QPushButton::clicked, [=] { decrease_ready_num(4); });
    back_player4->hide();

    buttons_player4.push_back(customize_player4);
    buttons_player4.push_back(ready_player4);
    buttons_player4.push_back(back_player4);

    scene->add_button(customize_player4);
    scene->add_button(ready_player4);
    scene->add_button(back_player4);
}