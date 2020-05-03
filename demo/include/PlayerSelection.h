#pragma once

#include <QGraphicsView>
#include <QLabel>
#include <vector>
#include "Player.h"
#include "Scene.h"

/*
 * For player selection new window is created in the beginning of the game.
 *  When all skins are selected, this window gets hidden (use it later)
 *  If this works, maybe should do the same to menu(s).
 */

class PlayerSelection : public QObject {
Q_OBJECT
public:

    PlayerSelection(Scene *scene);

    ~PlayerSelection() override;

    void add_players(const std::vector<Player *> &players);

    void run_player_selection();

    void clear_player_selection();

    void init_window();

    void set_text();

    void set_buttons();

    void set_images();

    void set_buttons_player1();

    void set_buttons_player2();

    void set_buttons_player3();

    void set_buttons_player4();


public slots:

    void change_image(int player_number);

    void increase_ready_num(int player_number);

    void decrease_ready_num(int player_number);

signals:

    void start_level();

private:
    Scene *scene;
    bool initialized = false;

    QLabel *character_selection;
    std::vector<QLabel *> player_num;

    std::vector<QPushButton *> buttons_player1;
    std::vector<QPushButton *> buttons_player2;
    std::vector<QPushButton *> buttons_player3;
    std::vector<QPushButton *> buttons_player4;
    QPushButton *customize_player1;
    QPushButton *customize_player2;
    QPushButton *customize_player3;
    QPushButton *customize_player4;
    QPushButton *ready_player1;
    QPushButton *ready_player2;
    QPushButton *ready_player3;
    QPushButton *ready_player4;
    QPushButton *back_player1;
    QPushButton *back_player2;
    QPushButton *back_player3;
    QPushButton *back_player4;

    std::vector<QString> available_skins{"images/demo_player.png", "images/demo_player_2.png"};
    std::vector<QGraphicsPixmapItem *> player_textures;
    std::vector<int> player_textures_index;
    int num_of_players = 0;
    int num_of_ready = 0;
    std::vector<Player *> players;
    const int MAX_NUM_OF_PLAYERS = 4;
};