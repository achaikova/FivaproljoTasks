#include "LevelStatistics.h"

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
    assert(1); // there shouldn't be a case in which we haven't found one
}

size_t get_player_index_by_color(Color color, LevelStatistics const &statistics) {
    for (int i = 0; i < statistics.players.size(); i++){
        if (color == statistics.players[i]->color){
            return i;
        }
    }
    assert(1); // there shouldn't be a case in which we haven't found one
}

void LevelStatistics::change_block_color(Block * block, Player * player) {
    if (block->get_color() == player->color){
        return;
    }
    // decrease stat for the color that has been changed
    player_statistic[get_player_index_by_color(block->get_color(), *this)]--;
    // increase stat for new color
    player_statistic[get_player_index(player, *this)]++;
}


// Returns an amount of blocks colored by a given player
size_t LevelStatistics::get_player_statistic(Player *player) const {
    return player_statistic[get_player_index(player, *this)];
}


                            // LEVEL STATISTICS TEST //


void LevelStatisticsTest::test() {

    // create players and give them colors
    Player *player_one  = new Player();
    Player *player_two  = new Player();
    player_one->color = Color::RED;
    player_two->color = Color::GREEN;
    std::vector<Player *> players{player_one, player_two};
    assert(players.size() == 2);
    assert(players[0] == player_one);
    assert(players[1] == player_two);

    // create stat
    LevelStatistics stat(players);
    assert(stat.get_blocks_amount() == DEMO_BLOCKS_AMOUNT);
    assert(stat.get_player_statistic(player_one) == 0);
    assert(stat.get_player_statistic(player_two) == 0);

    // create blocks
    QString default_block_texture = "images/1block.jpg";
    QPoint default_position(0,0);
    auto *block1 = new Block(default_position, default_block_texture);
    auto *block2 = new Block(default_position, default_block_texture);

    // case 1. Blocks are not colored
    stat.change_block_color(block1, player_one);
    stat.change_block_color(block2, player_two);
    assert(stat.get_player_statistic(player_one) == 1);
    assert(stat.get_player_statistic(player_two) == 1);

    block1->add_color(player_one->color);
    block2->add_color(player_two->color);

    // case 2. Color is the same

    stat.change_block_color(block1, player_one);
    stat.change_block_color(block2, player_two);
    assert(stat.get_player_statistic(player_one) == 1);
    assert(stat.get_player_statistic(player_two) == 1);

    // case 3. Change from one color to another

    stat.change_block_color(block1, player_two);
    assert(stat.get_player_statistic(player_one) == 0);
    assert(stat.get_player_statistic(player_two) == 2);
    block1->add_color(player_two->color);

    stat.change_block_color(block2, player_one);
    assert(stat.get_player_statistic(player_one) == 1);
    assert(stat.get_player_statistic(player_two) == 1);
    block2->add_color(player_one->color);
}
