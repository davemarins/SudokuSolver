#define UNASSIGNED 0
#define M 3
#define N 9

#include <bits/stdc++.h>
#include <string>
#include "Sudoku.h"

using namespace std;

int main(int argc, char *argv[]) {
    Sudoku *s = new Sudoku("sudoku.txt");
    s->printGrid();
    if(s->solve() == Solved) {
        s->printSolution();
        return 0;
    } else {
        cout << "" << endl;
        return -1;
    }
}
