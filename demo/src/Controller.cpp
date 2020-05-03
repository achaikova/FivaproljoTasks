#include <vector>
#include <QApplication>
#include <QTimer>
#include "Controller.h"

/*
 * Из контроллера осуществляется управление игровым процессом.
 * Изначально запускается окно с выбором количества игроков (runGame). При выборе посылается сигнал StateMachine::set_num_of_players,
 * после чего запускается окно с выбором скинов игроков Controller::set_num_of_players_for_lvl.
 * Когда все игроки готовы, (PlayerSelection::start_level -> StateMachine::start_level ->
 * StateMachine::set_level -> Controller::run_level) начинается уровень, который пока длится 10 секунд.
 * По окончании level_durance выводится статистика по уровню : Controller::end_level.
 * В появившемся окне статистики можно выбрать следующий режим игры.
 */

Controller::Controller(int argc, char *argv[])
        : app(argc, argv), scene_(new Scene()), key_presser_(new KeyPresser()),
          state_machine_(new StateMachine()), model_(new Model(scene_, state_machine_)),
          menu_(new Menu(scene_, state_machine_)),
          key_presser_helper_(new KeyPresserHelper(key_presser_)), player_selection(new PlayerSelection(scene_)) {
    key_presser_->setFixedSize(QSize(scene_->get_width(), scene_->get_height()));
    scene_->addWidget(key_presser_);
    connect(state_machine_, &StateMachine::set_num_of_players, this, &Controller::set_num_of_players_for_lvl);
    connect(state_machine_, &StateMachine::set_exit_game, this, &Controller::exit_game);
    connect(player_selection, &PlayerSelection::start_level, state_machine_, &StateMachine::start_level);
    connect(state_machine_, &StateMachine::set_level, this, &Controller::run_level);
    connect(state_machine_, &StateMachine::set_end_level, this, &Controller::end_level);
}

Controller::~Controller() {
    player_selection->~PlayerSelection();
    menu_->~Menu();
}

/*
 * Запускает стартововый экран с выбором количества персонажей; get_cur_state = MENU_NUM_OF_PLAYERS
 */
int Controller::run_game() {
    menu_->run_menu(state_machine_->get_cur_state());
    return app.exec();
}

/*
 * Добавляет нужное количество персонажей и запускает окно с выбором текстур для персонажей
 */
void Controller::set_num_of_players_for_lvl(Utilities::GameNumOfPlayers num) {
    switch (num) {
        case Utilities::GameNumOfPlayers::SINGLE_PLAYER:
            players_.push_back(new Player(Utilities::Color::GREEN));
            key_presser_->add_players(players_[0]);
            break;
        case Utilities::GameNumOfPlayers::TWO_PLAYERS:
            players_.push_back(new Player(Utilities::Color::GREEN));
            players_.push_back(new Player(Utilities::Color::YELLOW));
            key_presser_->add_players(players_[0], players_[1]);
            break;
    }
    run_player_selection();
}

/*
 * Прячет предыдущее окно меню. Открывается новое окно с выбором текстур.
 */
void Controller::run_player_selection() {
    menu_->clear_menu();
    player_selection->add_players(players_);
    player_selection->run_player_selection();
}

/*
 * Когда все игроки готовы, начинает уровень.
 */
void Controller::run_level(Utilities::GameMode mode) {
    player_selection->clear_player_selection();
    menu_->clear_menu();
    model_->add_players(players_);
    model_->set_statistics();
    model_->make_new_level();
    level_durance = new QTimer(this);
    connect(level_durance, SIGNAL(timeout()), state_machine_, SLOT(end_level()));
    connect(level_durance, SIGNAL(timeout()), model_, SLOT(stop_advance_scene()));
    level_durance->start(7000);
}

/*
 * По истечении времени останавливает таймер, останавливает игроков, выводит статистику.
 */
void Controller::end_level() {
    level_durance->stop();
    model_->show_statistics();
}

/*
 * При выборе выхода из игры заканчивает процессы, выходит из приложения.
 */
void Controller::exit_game() {
    app.quit();
}