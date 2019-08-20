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
    int recursion_times = 0;
    int grid[N][N];
    int solution[N][N];
    enum Solvable s = NotSolved;
    // Function to solve the Sudoku puzzle
    bool realSolve(int grid[N][N]);
    bool isValid(int grid[N][N], int row, int col, int num);
    bool isUsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num);
    bool isUsedInCol(int grid[N][N], int col, int num);
    bool isUsedInRow(int grid[N][N], int row, int num);
    bool findEmptyValues(int grid[N][N], int &row, int &col);
public:
    Sudoku(string filename);
    void printGrid();
    void printSolution();
    enum Solvable solve();
};

#endif //SUDOKUSOLVER_SUDOKU_H
