#ifndef SOLVER_H_
#define SOLVER_H_


void solver_solveBoard(int** mat, int size, int** matNew);
void solver_randomize();
void solver_randomizeBacktracking();
bool solver_is_legalValue(int **matrixPlay, int x, int y, int checked_value);
int solver_determenistic_algo(int **matrixPlay,int **matrixSolve);

#endif
