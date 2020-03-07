#include <iostream>
#include "StdioBoardView.h"
#include "Board.h"

StdioBoardView::StdioBoardView(Board& board, bool is_silent)
	: View(board)
	, is_silent_(is_silent)
{}

void StdioBoardView::printSymb(int x, int y) {
	if (board_.board_[x][y] == Board::NONE)
		std::cout << '.';
	if (board_.board_[x][y] == Board::PLAYER_O)
		std::cout << 'O';
	if (board_.board_[x][y] == Board::PLAYER_X)
		std::cout << 'X';
}

void StdioBoardView::showBoard() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			printSymb(i, j);
		std::cout << std::endl;
	}
}

bool StdioBoardView::get_move(Move& move) {
	std::string input;
	getline(std::cin, input);
	for (char ch : input)  // Only digits and spaces and '-'
		if (ch != ' ' and ch != '-' and ('0' > ch or ch > '9'))
			return false;
	for (unsigned int i = 0; i < input.size(); i++) // '-' only before number
		if (input[i] == '-' and i != 0 and input[i - 1] != ' ')
			return false;
	unsigned int i = 0;
	while (input[i] == ' ') {  // Skip spaces in beginning
		i++;
		if (i == input.size())
			return false;
	}
	while (input[i] != ' ') {  // Skip digits of first number
		i++;
		if (i == input.size())
			return false;
	}
	while (input[i] == ' ') {  // Skip spaces in between
		i++;
		if (i == input.size())
			return false;
	}
	while (i < input.size() and input[i] != ' ') {  // Skip digits of second number
		i++;
	}
	while (i < input.size()) {  // If exists third number
		if (input[i] != ' ')
			return false;
		i++;
	}
	std::stringstream str;
	str << input;
	str >> move.x >> move.y;
    return board_.canMove(move.x, move.y) or (move.x == -1 and move.y == -1);
}

void StdioBoardView::refreshBoard(Move move, Board::Player player) {
    unused(move);
    if (!is_silent_) showBoard();
    if (player == Board::PLAYER_O) std::cout << "O move: ";
    if (player == Board::PLAYER_X) std::cout << "X move: ";
}

bool StdioBoardView::getInput(Move& move, Board::Player player) {
    while (!get_move(move)) {
        sayBadMove();
        if (player == Board::PLAYER_O) std::cout << "O move: ";
        if (player == Board::PLAYER_X) std::cout << "X move: ";
    }
    return !(move.x == -1 and move.y == -1);
}

void StdioBoardView::sayBadMove() {
    std::cout << "Bad Move!" << "\n";
}

void StdioBoardView::sayMoveDone() {
    std::cout << "\n";
}

void StdioBoardView::showResult() {
    showBoard();
    if (board_.isWin() == Board::O_WON)
        std::cout << "O wins!" << std::endl;
    if (board_.isWin() == Board::X_WON)
        std::cout << "X wins!" << std::endl;
    if (board_.isWin() == Board::DRAW)
        std::cout << "Draw." << std::endl;
}
