#include "Board.h"
#include "BoardTest.h"
#include "Test.h"


int Test::failedNum = 0;
int Test::totalNum = 0;

int main() {
	BoardTest bt;
	bt.runAllTests();
	return BoardTest::showFinalResult();
}
