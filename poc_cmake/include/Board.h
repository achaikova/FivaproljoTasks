#pragma once

#define unused(p); (void)p;

class Board {
public:
	enum BoardState {
		IN_PROGRESS,
		DRAW,
		O_WON,
		X_WON
	};
	enum Player : unsigned char {
	    PLAYER_O = 0,
	    PLAYER_X = 1,
	    NONE = 2,
	};
	Board();
	~Board();
	void move(int x, int y, Player player);
	bool canMove(int x, int y, Player player = NONE);
	BoardState isWin();

private:	
	bool checkWin(int x, int y, Player player);
    int countRows(int x, int y, Player player, int x_increaser, int y_increaser) const;
	int countVert(int x, int y, Player player) const; // |
	int countHor(int x, int y, Player player) const;  // -
	int countDiag1(int x, int y, Player player) const;// /
	int countDiag2(int x, int y, Player player) const;// '\'

	static void nextPlayer(Player& player);

	Player** board_;
	BoardState board_state_;
	int turnsMade_;

	friend class StdioBoardView;
	friend class NcursesView;
	friend class GameController;
};
