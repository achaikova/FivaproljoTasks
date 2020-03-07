#pragma once

#include "View.h"
#include "Board.h"
#include "StdioBoardView.h"

class GameController {
public:
    GameController() = delete;
    GameController(Board& b, View& v);
    void runGame();

private:
    View& view_;
    Board& board_;
};