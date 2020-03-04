#include "NcursesBoardView.h"
#include <ncurses.h>
#include "Board.h"
#include "View.h"
#include "GameController.h"

NcursesView::NcursesView(Board& board)
    : View(board) {
    initscr();
    cbreak();
    noecho();
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    win = newwin(11, 10, max_y / 2 - 6, max_x / 2 - 5);
    refresh();
    keypad(win, TRUE);
    curs_set(0);
}

NcursesView::~NcursesView() {
    curs_set(1);
    delwin(win);
    delwin(stdscr);
    endwin();
    refresh();
}

void NcursesView::refreshBoard(Move move, Board::Player player) {
    showBoard(move.x, move.y);
    if (player == Board::PLAYER_O) wprintw(win, "O move:");
    if (player == Board::PLAYER_X) wprintw(win, "X move:");
    wrefresh(win);
}
void NcursesView::sayMoveDone() {}

void NcursesView::sayBadMove() {}

void NcursesView::showResult() {
    showBoard(-1, -1);
    if (board_.isWin() == Board::BoardState::O_WON)
        wprintw(win, "O wins!");
    else if (board_.isWin() == Board::BoardState::X_WON)
        wprintw(win, "X wins!");
    else if (board_.isWin() == Board::BoardState::DRAW)
        wprintw(win, "Draw.  ");
    wrefresh(win);
    wgetch(win);
}

void NcursesView::printSymb(int x, int y) const {
    if (board_.board_[x][y] == Board::NONE)
        mvwaddch(win, y, x, '.');
    if (board_.board_[x][y] == Board::PLAYER_O)
        mvwaddch(win, y, x, 'O');
    if (board_.board_[x][y] == Board::PLAYER_X)
        mvwaddch(win, y, x, 'X');
}

void NcursesView::showBoard(int x, int y) const {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (i == x and j == y)
                wattron(win, A_REVERSE);
            printSymb(i, j);
            wattroff(win, A_REVERSE);
        }
}

bool NcursesView::getInput(Move &move, Board::Player player) {
    int mv;
    while (true) {
        mv = wgetch(win);
        if (mv == KEY_LEFT or mv == (int)'a') {
            move.x = (move.x > 0 ? move.x - 1 : move.x);
            refreshBoard(move, player);
        }
        if (mv == KEY_RIGHT or mv == (int)'d') {
            move.x = (move.x < 9 ? move.x + 1 : move.x);
            refreshBoard(move, player);
        }
        if (mv == KEY_DOWN or mv == (int)'s') {
            move.y = (move.y < 9 ? move.y + 1 : move.y);
            refreshBoard(move, player);
        }
        if (mv == KEY_UP or mv == (int)'w') {
            move.y = (move.y > 0 ? move.y - 1 : move.y);
            refreshBoard(move, player);
        }
        if (mv == (int)' ' and board_.canMove(move.x, move.y, player))
            return true;
        if (mv == (int)'x')
            return false;
    }
}
