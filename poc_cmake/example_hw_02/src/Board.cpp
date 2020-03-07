#include "Board.h"
#include <iostream>

Board::Board()
	: board_state_(IN_PROGRESS)
	, turnsMade_(0)
{
	board_ = new Player* [10];
	Player* temp = new Player [100];
	for (int i = 0; i < 10; i++) {
		board_[i] = &temp[10 * i];
	}
	for (int i = 0; i < 100; i++) {
		temp[i] = NONE;
	}
}

Board::~Board() {
	delete[] board_[0];
	delete[] board_;
}

void Board::move(int x, int y, Player player) {
	board_[x][y] = player;
	if (++turnsMade_ >= 100) board_state_ = DRAW;
	if (checkWin(x, y, player)) board_state_ = player == PLAYER_O ? O_WON : X_WON;
}

bool Board::canMove(int x, int y, Player player) {
	unused(player); // Ну там в задании дана такая сигнатура, я собственно не стал ее менять
	if (0 <= x and x <= 9 and 0 <= y and y <= 9)
		return board_[x][y] == NONE;
	return false;
}

Board::BoardState Board::isWin() {
	return board_state_;
}

bool Board::checkWin(int x, int y,  Player player) {
    return countRows(x, y, player, 0, 1) >= 5 or
           countRows(x, y, player, 1, 0) >= 5 or
           countRows(x, y, player, 1, -1) >= 5 or
           countRows(x, y, player, 1, 1) >= 5;
}

int Board::countRows(int x, int y, Player player, int x_increaser, int y_increaser) const {
    int counter = 1;
    int y_offset = y_increaser;
    int x_offset = x_increaser;
    while (0 <= y + y_offset and y + y_offset <= 9 and
           0 <= x + x_offset and x + x_offset <= 9 and
           board_[x + x_offset][y + y_offset] == player) {
        counter++;
        x_offset += x_increaser;
        y_offset += y_increaser;
    }
    y_offset = - y_increaser;
    x_offset = - x_increaser;
    while (0 <= y + y_offset and y + y_offset <= 9 and
           0 <= x + x_offset and x + x_offset <= 9 and
           board_[x + x_offset][y + y_offset] == player) {
        counter++;
        x_offset -= x_increaser;
        y_offset -= y_increaser;
    }
    return counter;
}

void Board::nextPlayer(Player& player) {
	if (player == PLAYER_O) player = PLAYER_X;
	else player = PLAYER_O;
}
