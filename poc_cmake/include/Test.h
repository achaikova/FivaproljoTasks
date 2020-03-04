#pragma once

#include <cstddef>

#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE_NAME__, __LINE__)

class Test {
public:
	static void check(bool expr, const char* func, const char* filename, std::size_t lineNum);
	static bool showFinalResult();
	virtual void runAllTests() = 0;
protected:
	static int failedNum; // количество тестов, которые сломались
	static int totalNum;  // общее количество тестов
};
