/*
 * Solver.h
 *
 *  Created on: Dec 11, 2018
 *      Author: eyal & nadin
 */


#ifndef SOLVER_H_
#define SOLVER_H_


/*void solver_solveBoard(int** mat, int size, int** matNew);*/

/*solver_randomizeBacktracking
 * Input: int** matrixSolve.
 * return: bool true or false.
 *  return false if matrix is not solvable. otherwise true.
 * the function receives matrix with the value of 0 in each cell.
 * for each cell the function chooses randomly a value from the legal values and place it.
 * the function continue to check all options for numbers to fill until all matrix is filled.
 * if after checking all options for one cell no value solve the board it returns false.
 */
bool solver_randomizeBacktracking(int** matrixSolve);

/*solver_is_legalValue
 * Input:
 * 		int** matrixPlay: pointer to the matrix the user play with.
 * 		int x: value of raw of a chosen cell
 * 		int y: value of columns of a chosen cell
 * 		int checked_value: the value which we are checking
 * return: bool true or false.
 * 		the function check whether the checked value can be placed in cell[x][y].
 * 		it can be placed if the checked value is not in the same raw,column and block.
 * 		if not it return false.
 */
bool solver_is_legalValue(int **matrixPlay, int x, int y, int checked_value);

/*solver_determenistic_algo
 * Input:
 * 		int** matrixPlay: current matrix that the user play with
 * 		int** matrixSolve: last updated solved solution to the matrix.
 * return: bool true/false
 * 		true if the matrix is solvable. in each empty cell the function try to put legal values from 1-9.
 * 		if after trying all options no solution found, it returns false.
 * 		otherwise if in all empty cells valid number have been placed, it returns true.
 */
bool solver_determenistic_algo(int **matrixPlay,int **matrixSolve);

#endif
