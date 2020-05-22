#include "LevelStatistics.h"
#include <cassert>

//  LEVEL STATISTICS  //

LevelStatistics::LevelStatistics(std::vector<Player *> &players, Scene *scene, StateMachine *state_machine)
        : state_machine(state_machine), players(players),
          player_statistic(std::vector<int>(players.size())),
          scene(scene),
          blocks_amount(DEMO_BLOCKS_AMOUNT) {}

void LevelStatistics::set_players(std::vector<Player *> &new_players) {
    players = new_players;
    player_statistic.resize(players.size());
}


// We dont have much players so it's fine not to optimize these two actions down here

size_t get_player_index(Player *player, LevelStatistics const &statistics) {
    for (int i = 0; i < statistics.players.size(); i++) {
        if (player == statistics.players[i]) {
            return i;
        }
    }
    assert(false); // there shouldn't be a case in which we haven't found one
}

size_t get_player_index_by_color(Utilities::Color color, LevelStatistics const &statistics) {
    for (int i = 0; i < statistics.players.size(); i++) {
        if (color == statistics.players[i]->color) {
            return i;
        }
    }
    assert(false); // there shouldn't be a case in which we haven't found one
}

void LevelStatistics::change_block_color(Block *block, Player *player) {
    if (block->get_color() == player->color) {
        return;
    }
    // decrease stat for the color that has been changed
    if (block->get_color() !=
        Utilities::Color::NONE) { // Если до этого цвета не было, не нужно инкриминтировать счетчик.
        player_statistic[get_player_index_by_color(block->get_color(), *this)]--;
        total_amount--;
    }
    // increase stat for new color
    player_statistic[get_player_index(player, *this)]++;
    total_amount++;
}


// Returns an amount of blocks colored by a given player
size_t LevelStatistics::get_player_statistic(Player *player) const {
    return player_statistic[get_player_index(player, *this)];
}

void LevelStatistics::run_level_statistic() {
    set_background();
    set_images();
    set_text();
    set_buttons();
}

void LevelStatistics::set_background() {
//    if (statistic_window) {
//        statistic_window->show();
//        return;
//    }
    statistic_window = new QGraphicsRectItem(0, 100, 1250, 500);
    statistic_window->setBrush(QBrush(QColor(50, 50, 50, 230)));
    scene->add_qgrectitem(statistic_window);
}

void LevelStatistics::set_images() {
    for (int i = 0; i < player_statistic.size(); i++) {
        int height = 130.0 * ((double) player_statistic[i] / (double) total_amount);
        QGraphicsRectItem *item = new QGraphicsRectItem(80 + i * 200, 580 - height, 150, height);
        item->setBrush(QBrush(block_colors[players[i]->color]));
        item->setPen(QPen(pen_colors[players[i]->color], 3));
        winning_pos.push_back(item);
        scene->add_qgrectitem(item);

        QGraphicsPixmapItem *player = new QGraphicsPixmapItem;
        player->setPixmap(QPixmap(players[i]->image).scaled(120, 120));
        player->setPos(85 + i * 200, 580 - height - 150);
        player_textures.push_back(player);
        scene->add_pixmap(player);
    }
}

void LevelStatistics::set_text() {
    if (next_game_text) {
        next_game_text->show();
        next_game_text->raise();
        return;
    }
    next_game_text = new QLabel();
    next_game_text->setText("NEXT GAME");
    next_game_text->move(1050, 120);
    QFont cs_f("Arial", 25);
    next_game_text->setFont(cs_f);
    next_game_text->setStyleSheet("QLabel {  color : grey; }");
    next_game_text->setAttribute(Qt::WA_TranslucentBackground);
    scene->add_text(next_game_text);
    next_game_text->show();
}

void LevelStatistics::set_buttons() {
    if (color_craze) {
        color_craze->show();
        color_craze->raise();
        return;
    }
    color_craze = new QPushButton("COLOR CRAZE");
    color_craze->setGeometry(QRect(QPoint(1000, 200),
                                   QSize(200, 50)));
    scene->add_button(color_craze);
    color_craze->show();
    connect(color_craze, &QPushButton::clicked, this, &LevelStatistics::clear_statistics);
    connect(color_craze, &QPushButton::clicked, state_machine, &StateMachine::start_level);
}

void LevelStatistics::clear_statistics() {
    for (auto i : player_textures) {
        scene->remove_item(i);
    }
    player_textures.clear();
    for (auto i: winning_pos) {
        scene->remove_item(i);
    }
    players.clear();
    player_statistic.clear();
    winning_pos.clear();
    scene->remove_item(statistic_window);
    next_game_text->hide();
    //statistic_window->hide();
    color_craze->hide();
}