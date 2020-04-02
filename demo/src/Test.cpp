#include "cstdio"
#include "Test.h"
#include <QDebug>

int Test::failed_tests = 0;
int Test::total_tests = 0;

// Проверка expression, подсчет тестов
void Test::check(bool expr, const char *func, const char  *file_name, size_t line_number){
    total_tests++;
    if (!expr){
        failed_tests++;
        qDebug() << "Failed at: " << file_name << "in function " << func <<
            "(): " << line_number << '\n';
    }
}

// Вывод результатов тестов
bool Test::show_final_result(){
    printf("Tests passed: %d\n", total_tests - failed_tests);
    printf("Tests failed: %d\n", failed_tests);
    if (!failed_tests){
        return !failed_tests;
    }
    return false;
}


