#pragma once

#include "Board.h"
#include "View.h"
#include <sstream>

class StdioBoardView : public View {
public:
	explicit StdioBoardView(Board& board, bool is_silent);
	StdioBoardView() = delete;
    void refreshBoard(Move move, Board::Player player) override;
    bool getInput(Move& move, Board::Player player) override;
    void sayBadMove() override;
    void sayMoveDone() override;
    void showResult() override;
private:
    bool get_move(Move& move);
    bool is_silent_;
    void showBoard();
	void printSymb(int x, int y);
    friend class GameController;
};
