cmake_minimum_required(VERSION 3.17)
project(AI)

set(CMAKE_CXX_STANDARD 14)

add_executable(AI main.cpp Point.h Point.cpp Sokoban.cpp Sokoban.h Astar.h Astar.cpp)