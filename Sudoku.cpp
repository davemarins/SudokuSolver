//
// Created by davide on 19/08/19.
//

#include <chrono>
#include <cstdlib>
#include <iostream>
#include "Sudoku.h"

using namespace std;

// Is there any 0s?
bool Sudoku::findEmptyValues(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

// Is it used in that row?
bool Sudoku::isUsedInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Is it used in that column?
bool Sudoku::isUsedInCol(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Is it already present in the MxM grid?
bool Sudoku::isUsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < M; row++)
        for (int col = 0; col < M; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}

// Checks given row, column and MxM grid
bool Sudoku::isValid(int grid[N][N], int row, int col, int num) {
    return !Sudoku::isUsedInRow(grid, row, num) && !Sudoku::isUsedInCol(grid, col, num) &&
           !Sudoku::isUsedInBox(grid, row - row % M, col - col % M, num)
           && grid[row][col] == UNASSIGNED;
}

// Real function to solve - it uses the stack with recursion
bool Sudoku::realSolve(int grid[N][N]) {
    Sudoku::recursion_times++;
    int row, col;
    if (!Sudoku::findEmptyValues(grid, row, col)) return true;
    for (int num = 1; num <= N; num++)
        if (Sudoku::isValid(grid, row, col, num)) {
            grid[row][col] = num;
            if (Sudoku::realSolve(grid)) return true;
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
    cout << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << Sudoku::grid[row][col] << "\t";
        cout << endl;
    }
    cout << endl;
}

void Sudoku::printSolution() {
    cout << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << Sudoku::solution[row][col] << "\t";
        cout << endl;
    }
    cout << endl;
}

enum Solvable Sudoku::solve() {
    Sudoku::recursion_times = 0;
    auto start = chrono::high_resolution_clock::now();
    if(Sudoku::realSolve(Sudoku::solution)) {
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Sudoku solved in " << Sudoku::recursion_times << " recursions" << endl;
        cout << "Time needed to solve: " << duration.count() << " microseconds" << endl;
        Sudoku::s = Solved;
        return Sudoku::s;
    } else {
        Sudoku::s = NonSolvable;
        return Sudoku::s;
    }
}
