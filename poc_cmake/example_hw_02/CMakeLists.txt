cmake_minimum_required(VERSION 3.15)

project(hw_02)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

SET(CMAKE_CXX_FLAGS  "-Wall -Wextra -Werror")

SET(CMAKE_EXE_LINKER_FLAGS  "-lncurses")

if(LINUX) 
    add_executable(hw_02
	     src/Board.cpp
      	     src/GameController.cpp
       	     src/main.cpp
   	     src/NcursesBoardView.cpp
             src/StdioBoardView.cpp
    	     src/View.cpp
       	     )
elseif(MACOSX)
    add_executable(hw_02_test
            src/Board.cpp
            test/BoardTest.cpp
            test/Test.cpp
            test/main_test.cpp
            )
endif()
