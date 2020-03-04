#pragma once

#include "View.h"
#include "Board.h"

struct Move {
    Move() = default;
    int x, y;
};

class View {
public:
    View(Board& board);
    View(const View&) = delete;
    View& operator=(const View&) = delete;
    virtual ~View() = default;
    virtual void refreshBoard(Move move, Board::Player player) = 0;
    virtual bool getInput(Move& move, Board::Player player) = 0;
    virtual void sayBadMove() = 0;
    virtual void sayMoveDone() = 0;
    virtual void showResult() = 0;
protected:
    Board& board_;
};