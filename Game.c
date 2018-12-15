#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"
#include "Game.h"
#include "Solver.h"

#include <stdlib.h>

#define ROWS 9
#define COLS 9

/*int matrixSolve[ROWS][COLS];
int matrixPlay[ROWS][COLS];*/
int rows,cols;
int **matrixSolve, **matrixPlay, **matrixfixed;


/*nadin- create the matrix  */
int **createMatrix(int rows, int col) {
	int **matrix, i;
	matrix = calloc(rows, sizeof(int *));
	if (matrix == NULL) {
		return NULL;
	}
	for (i = 0; i < 9; i++) {
		matrix[i] = calloc(col, sizeof(int));
		if (matrix[i] == NULL) {
			return NULL;
		}
	}
	return matrix;
}
void game_randomlyPickFixCells(){

}

/**
 * create empty board
 * use randomized backtracking to get random solve board
 * repeat fix cell H time
 */
void game_create(int rows, int cols ,int fixCell, int seed){
	//matrixSolve = (int *)calloc(rows * cols , sizeof(Cell));
	matrixSolve = createMatrix(rows,col);
	matrixPlay=createMatrix(rows,col);
	matrixfixed= createMatrix(rows, col);
	printBoard(matrixPlay,  matrixfixed);
	solver_randomizeBacktracking(matrixSolve,rows,cols);
	game_randomlyPickFixCells();
}

/*bool game_isGameFinish(){

}*/

ADTErr game_playTurn(Command command){
	switch(command.func){
		case SET:
		{
			game_set();
		} break;
		case HINT:
		{
			game_hint();
		} break;
		case VALIDATE:
		{
			game_validate();
		} break;
	}
	return ERR_OK;
}

ADTErr game_set(){
	//game_fix?
	//game_isValid() contain the neighbors
	return ERR_OK;
}

ADTErr game_hint(){
	return ERR_OK;
}

ADTErr game_validate(){
	return ERR_OK;
}
	//err = solver_solveBoard(mat, size, matNew  )

