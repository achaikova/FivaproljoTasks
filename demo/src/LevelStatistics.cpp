#include "LevelStatistics.h"
#include <cassert>

                            //  LEVEL STATISTICS  //

LevelStatistics::LevelStatistics(std::vector<Player *> &players)
    : players(players)
    , player_statistic(std::vector<int>(players.size()))
    , blocks_amount(DEMO_BLOCKS_AMOUNT)
{}

// We dont have much players so it's fine not to optimize these two actions down here

size_t get_player_index(Player * player, LevelStatistics const &statistics) {
    for (int i = 0; i < statistics.players.size(); i++){
        if (player == statistics.players[i]){
            return i;
        }
    }
    assert(false); // there shouldn't be a case in which we haven't found one
}

size_t get_player_index_by_color(Utilities::Color color, LevelStatistics const &statistics) {
    for (int i = 0; i < statistics.players.size(); i++){
        if (color == statistics.players[i]->color){
            return i;
        }
    }
    assert(false); // there shouldn't be a case in which we haven't found one
}

void LevelStatistics::change_block_color(Block * block, Player * player) {
    if (block->get_color() == player->color){
        return;
    }
    // decrease stat for the color that has been changed
    if (block->get_color() != Utilities::Color::NONE){ // Если до этого цвета не было, не нужно инкриминтировать счетчик.
        player_statistic[get_player_index_by_color(block->get_color(), *this)]--;
    }
    // increase stat for new color
    player_statistic[get_player_index(player, *this)]++;
}


// Returns an amount of blocks colored by a given player
size_t LevelStatistics::get_player_statistic(Player *player) const {
    return player_statistic[get_player_index(player, *this)];
}
