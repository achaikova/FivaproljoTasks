#pragma once

#include <vector>
#include "Player.h"
#include "Block.h"
const size_t DEMO_BLOCKS_AMOUNT = 108; // at this point we have only one map

/* Класс для хранения всей необходимой статистики на игровом поле
 * На данный момент хранит общее количество блоков и соотносит
 * для каждого игрока кол-во закрашенных им блоков */

class LevelStatistics {
public:
    LevelStatistics(std::vector<Player *> &players);
    void change_block_color(Block *, Player *);
    size_t get_player_statistic(Player *) const;
    size_t get_blocks_amount() const {return blocks_amount; };

    friend size_t get_player_index(Player *, LevelStatistics const&);
    friend size_t get_player_index_by_color(Color, LevelStatistics const&);
private:
    std::vector<Player *> players;
    std::vector<int> player_statistic;
    size_t blocks_amount;
};
