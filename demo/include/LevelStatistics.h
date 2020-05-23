#pragma once

#include <vector>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <cmath>
#include <unordered_map>
#include "Block.h"
#include "StateMachine.h"
#include "Player.h"
#include "Scene.h"

const size_t DEMO_BLOCKS_AMOUNT = 108; // at this point we have only one map

/* Класс для хранения всей необходимой статистики на игровом поле
 * На данный момент хранит общее количество блоков и соотносит
 * для каждого игрока кол-во закрашенных им блоков */

class LevelStatistics : public QObject {
Q_OBJECT
public:
    LevelStatistics(std::vector<Player *> &players, Scene *scene, StateMachine *state_machine);

    void change_block_color(Block *, Player *);

    void set_players(std::vector<Player *> &players);

    size_t get_player_statistic(Player *) const;

    size_t get_blocks_amount() const { return blocks_amount; };

    friend size_t get_player_index(Player *, LevelStatistics const &);

    friend size_t get_player_index_by_color(Utilities::Color, LevelStatistics const &);

    void run_level_statistic();

    void set_buttons();

    void set_text();

    void set_images();

    void set_background();

public slots:

    void clear_statistics();
    // void choose_level();

signals:

    // void set_level();

private:
    Scene *scene;
    StateMachine *state_machine;
    QLabel *next_game_text = nullptr;
    QGraphicsRectItem *statistic_window = nullptr;
    std::vector<QPushButton *> next_game_buttons;
    // QGraphicsProxyWidget *proxy;
    std::vector<QGraphicsRectItem *> winning_pos;
    std::vector<QGraphicsPixmapItem *> player_textures;
    QPushButton *color_craze = nullptr;
    std::vector<Player *> players;
    std::vector<int> player_statistic;
    size_t blocks_amount;
    int total_amount = 0;
    std::unordered_map<Utilities::Color, QColor>
            block_colors{{Utilities::Color::GREEN,  QColor(54, 134, 15)},
                         {Utilities::Color::YELLOW, QColor(168, 140, 10)}};
    std::unordered_map<Utilities::Color, QColor>
            pen_colors{{Utilities::Color::GREEN,  QColor(30, 84, 7)},
                       {Utilities::Color::YELLOW, QColor(105, 87, 7)}};
};