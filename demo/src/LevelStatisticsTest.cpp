#include "include/LevelStatisticsTest.h"
#include "LevelStatistics.h"

#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__);

void LevelStatisticsTest::test_basic_functionality() {

    // create players and give them colors
    Player *player_one  = new Player();
    Player *player_two  = new Player();
    player_one->color = Color::RED;
    player_two->color = Color::GREEN;
    std::vector<Player *> players{player_one, player_two};
    DO_CHECK(players.size() == 2);
    DO_CHECK(players[0] == player_one);
    DO_CHECK(players[1] == player_two);

    // create stat
    LevelStatistics stat(players);
    DO_CHECK(stat.get_blocks_amount() == DEMO_BLOCKS_AMOUNT);
    DO_CHECK(stat.get_player_statistic(player_one) == 0);
    DO_CHECK(stat.get_player_statistic(player_two) == 0);

    // create blocks
    QString default_block_texture = "images/1block.jpg";
    QPoint default_position(0,0);
    auto *block1 = new Block(default_position, default_block_texture);
    auto *block2 = new Block(default_position, default_block_texture);

    // case 1. Blocks are not colored
    stat.change_block_color(block1, player_one);
    stat.change_block_color(block2, player_two);
    DO_CHECK(stat.get_player_statistic(player_one) == 1);
    DO_CHECK(stat.get_player_statistic(player_two) == 1);

    block1->change_color_for_test(player_one->color);
    block2->change_color_for_test(player_two->color);

    // case 2. Color is the same

    stat.change_block_color(block1, player_one);
    stat.change_block_color(block2, player_two);
    DO_CHECK(stat.get_player_statistic(player_one) == 1);
    DO_CHECK(stat.get_player_statistic(player_two) == 1);

    // case 3. Change from one color to another

    stat.change_block_color(block1, player_two);
    DO_CHECK(stat.get_player_statistic(player_one) == 0);
    DO_CHECK(stat.get_player_statistic(player_two) == 2);
    block1->change_color_for_test(player_two->color);

    stat.change_block_color(block2, player_one);
    DO_CHECK(stat.get_player_statistic(player_one) == 1);
    DO_CHECK(stat.get_player_statistic(player_two) == 1);
    block2->change_color_for_test(player_one->color);

    // free data
    delete player_one;
    delete player_two;
    delete block1;
    delete block2;
}

void LevelStatisticsTest::run_all_tests(){
    test_basic_functionality();
}