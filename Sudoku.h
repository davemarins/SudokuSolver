//
// Created by davide on 19/08/19.
//

#ifndef SUDOKUSOLVER_SUDOKU_H
#define SUDOKUSOLVER_SUDOKU_H

#define UNASSIGNED 0
#define M 3
#define N 9

#include <string>

using namespace std;

enum Solvable {
    NonSolvable = -1,
    NotSolved = 0,
    Solved = 1
};

class Sudoku {
private:
    int grid[N][N];
    int solution[N][N];
    enum Solvable s = NotSolved;
public:
    Sudoku(string filename);
    void printGrid();
    void printSolution();
    enum Solvable solve();
};

#endif //SUDOKUSOLVER_SUDOKU_H
