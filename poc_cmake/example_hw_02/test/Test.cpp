#include <iostream>
#include <cstddef>
#include "Test.h"

void Test::check(bool expr, const char* func, const char* filename, std::size_t lineNum) {
	if (!expr) {
		std::cout << "test failed: " << func << "() in " << filename << ":" << lineNum << std::endl;
		failedNum++;
	}
	totalNum++;
}

bool Test::showFinalResult() {
	if (!failedNum) std::cout << "All tests passed" << std::endl;
	else std::cout << "Failed " << failedNum << " of " << totalNum << " tests" << std::endl;
	return failedNum;
}