#pragma once

#include "Test.h"

class BoardTest : public Test {
public:
	void runAllTests() override;

private:
	void testIsWin1();
	void testIsWin2();
	void testIsWin3();
	
	void testMove1();
	void testMove2();
	void testMove3();

	void testCanMove1();
	void testCanMove2();
	void testCanMove3();
};
