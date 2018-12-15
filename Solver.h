#ifndef SOLVER_H_
#define SOLVER_H_


void solver_solveBoard(int** mat, int size, int** matNew);
void solver_randomize();
void solver_randomizeBacktracking();
bool solver_is_legalvalue(int **matrixPlay, int row, int col, int checked_value);

#endif
