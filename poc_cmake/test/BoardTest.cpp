#include "BoardTest.h"
#include "Board.h"

void BoardTest::runAllTests(){
	testIsWin1();
	testIsWin2();
	testIsWin3();
	
	testMove1();
	testMove2();
	testMove3();
	
	testCanMove1();
	testCanMove2();
	testCanMove3();
}

void BoardTest::testIsWin1() {
	Board b;
	b.move(0, 0, Board::PLAYER_O);
	b.move(1, 1, Board::PLAYER_O);
	b.move(2, 2, Board::PLAYER_O);
	b.move(3, 3, Board::PLAYER_X);
	b.move(4, 4, Board::PLAYER_X);
	b.move(5, 5, Board::PLAYER_O);
	b.move(6, 6, Board::PLAYER_O);
	b.move(7, 7, Board::PLAYER_O);
	b.move(8, 8, Board::PLAYER_X);
	b.move(9, 9, Board::PLAYER_X);
	DO_CHECK(b.isWin() == Board::BoardState::IN_PROGRESS);
}

void BoardTest::testIsWin2() {
	Board b;
	b.move(0, 0, Board::PLAYER_O);
	b.move(1, 1, Board::PLAYER_O);
	b.move(2, 2, Board::PLAYER_O);
	b.move(3, 3, Board::PLAYER_O);
	b.move(4, 5, Board::PLAYER_X);
	b.move(5, 5, Board::PLAYER_O);
	b.move(6, 6, Board::PLAYER_O);
	b.move(7, 7, Board::PLAYER_O);
	b.move(8, 8, Board::PLAYER_X);
	b.move(4, 4, Board::PLAYER_O);
	DO_CHECK(b.isWin() == Board::BoardState::O_WON);
}

void BoardTest::testIsWin3() {
	Board b;
	b.move(9, 0, Board::PLAYER_O);
	b.move(1, 1, Board::PLAYER_X);
	b.move(9, 2, Board::PLAYER_O);
	b.move(0, 0, Board::PLAYER_X);
	b.move(9, 5, Board::PLAYER_O);
	b.move(2, 2, Board::PLAYER_X);
	b.move(9, 6, Board::PLAYER_O);
	b.move(3, 3, Board::PLAYER_X);
	b.move(9, 8, Board::PLAYER_O);
	b.move(4, 4, Board::PLAYER_X);
	DO_CHECK(b.isWin() == Board::BoardState::X_WON);
}

void BoardTest::testMove1() {
	Board b;
	b.move(1, 1, Board::PLAYER_O);
	DO_CHECK(!b.canMove(1, 1, Board::PLAYER_X));
}

void BoardTest::testMove2() {
	Board b;
	b.move(1, 1, Board::PLAYER_O);
	DO_CHECK(b.canMove(1, 4, Board::PLAYER_X));
}

void BoardTest::testMove3() {
	Board b;
	b.move(7, 1, Board::PLAYER_O);
	DO_CHECK(!b.canMove(7, 1, Board::PLAYER_X));
}

void BoardTest::testCanMove1() {
	Board b;
	b.move(2, 1, Board::PLAYER_O);
	DO_CHECK(!b.canMove(2, 1, Board::PLAYER_X));
}

void BoardTest::testCanMove2() {
	Board b;
	b.move(1, 1, Board::PLAYER_O);
	DO_CHECK(b.canMove(1, 4, Board::PLAYER_O));
}

void BoardTest::testCanMove3() {
	Board b;
	b.move(7, 4, Board::PLAYER_X);
	DO_CHECK(b.canMove(7, 1, Board::PLAYER_X));
}
