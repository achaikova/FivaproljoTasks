#pragma once

#include <ncurses.h>
#include "Board.h"
#include <curses.h>
#include "View.h"

class NcursesView : public View {
public:
    NcursesView() = delete;
    ~NcursesView() override;
    explicit NcursesView(Board& board);
    void refreshBoard(Move move, Board::Player player) override;
    void sayMoveDone() override;
    void sayBadMove() override;
    void showResult() override;
    bool getInput(Move& move, Board::Player player) override;

private:
    void printSymb(int x, int y) const;
    void showBoard(int x, int y) const;
    WINDOW* win;
};
