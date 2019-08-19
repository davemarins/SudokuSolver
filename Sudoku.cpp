//
// Created by davide on 19/08/19.
//

#include <cstdlib>
#include <iostream>
#include "Sudoku.h"

using namespace std;

// Searches the grid to find an entry that is still unassigned. If found, the reference parameters row, col will be
// set the location that is unassigned, and true is returned. If no unassigned entries remain, false is returned
bool FindUnassignedLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

// Returns a boolean which indicates whether an assigned entry in the specified row matches the given number
bool UsedInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Returns a boolean which indicates whether an assigned entry in the specified column matches the given number
bool UsedInCol(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Returns a boolean which indicates whether an assigned entry within the specified 3x3 box matches the given number
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < M; row++)
        for (int col = 0; col < M; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}

// Returns a boolean which indicates whether it will be legal to assign num to the given row, col location
bool isSafe(int grid[N][N], int row, int col, int num) {
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row % M, col - col % M, num)
           && grid[row][col] == UNASSIGNED;
}

// Takes a partially filled-in grid and attempts to assign values to all unassigned locations in such a way to meet
// the requirements for Sudoku solution (non-duplication across rows, columns, and boxes)
bool SolveSudoku(int grid[N][N]) {
    int row, col;
    if (!FindUnassignedLocation(grid, row, col)) return true;
    for (int num = 1; num <= N; num++)
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (SolveSudoku(grid)) return true;
            grid[row][col] = UNASSIGNED;
        }
    return false;
}

Sudoku::Sudoku(string filename) {
    int temp;
    FILE *f = fopen(filename.data(), "r");
    if(f == nullptr) exit(-1);
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N && fscanf(f, "%d,", &temp); j++) {
            Sudoku::grid[i][j] = (int) temp;
            Sudoku::solution[i][j] = (int) temp;
        }
}

void Sudoku::printGrid() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << Sudoku::grid[row][col] << "\t";
        cout << endl;
    }
    cout << endl;
}

void Sudoku::printSolution() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << Sudoku::solution[row][col] << "\t";
        cout << endl;
    }
    cout << endl;
}

enum Solvable Sudoku::solve() {
    if(SolveSudoku(Sudoku::solution)) {
        Sudoku::s = Solved;
        return Sudoku::s;
    } else {
        Sudoku::s = NonSolvable;
        return Sudoku::s;
    }
}
