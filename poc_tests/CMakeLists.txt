cmake_minimum_required(VERSION 3.14)
project(lab_12)

set(CMAKE_CXX_STANDARD 17)
include_directories(include test/data)
add_subdirectory(test)
add_subdirectory(lib/googletest)