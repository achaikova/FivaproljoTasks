#pragma once

#define my_defined_main int main() {\
	Board board;;\
	NcursesView view(board);\
	GameController gc(board, view);\
	gc.runGame();\
	return 0;\
}\
