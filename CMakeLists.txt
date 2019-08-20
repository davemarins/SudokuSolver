cmake_minimum_required(VERSION 3.14)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(SudokuSolver main.cpp Sudoku.cpp Sudoku.h sudoku.txt)