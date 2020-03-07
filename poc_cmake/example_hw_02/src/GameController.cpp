#include "GameController.h"
#include "View.h"
#include "Board.h"

GameController::GameController(Board& b, View& v)
    : view_(v)
    , board_(b)
{}

void GameController::runGame() {
    Board::Player player = Board::PLAYER_O;
    Move move{};
    while (board_.isWin() == Board::IN_PROGRESS) {
        view_.refreshBoard(move, player);
        if (view_.getInput(move, player)) {
            if (board_.canMove(move.x, move.y))
                board_.move(move.x, move.y, player);
        }
        else
            return;
        Board::nextPlayer(player);
        view_.sayMoveDone();
    }
    view_.showResult();
}
