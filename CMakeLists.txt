cmake_minimum_required(VERSION 3.14)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 11)

add_executable(SudokuSolver main.cpp Sudoku.cpp Sudoku.h sudoku.txt)