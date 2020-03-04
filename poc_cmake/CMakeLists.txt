cmake_minimum_required(VERSION 3.15)

project(hw_02)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

SET(CMAKE_CXX_FLAGS  "-Wall -Wextra -Werror")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

SET(CMAKE_EXE_LINKER_FLAGS  "-lncurses")

add_executable(hw_02
        src/Board.cpp
        src/GameController.cpp
        src/main.cpp
        src/NcursesBoardView.cpp
        src/StdioBoardView.cpp
        src/View.cpp
        )

add_executable(hw_02_test
        src/Board.cpp
        test/BoardTest.cpp
        test/Test.cpp
        test/main_test.cpp
        )
