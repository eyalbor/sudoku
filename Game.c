#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"
#include "Game.h"
#include "Solver.h"

#include <stdlib.h>

#define ROWS 9
#define COLS 9

int **matrixSolve, **matrixPlay, **matrixfixed;
//int matrixSolver[ROWS][COLS];
//int matrixPlay[ROWS][COLS];
int rows,cols;
int puzzle[9][9]={{0, 0, 0, 0, 0, 0, 0, 9, 0},
                     {1, 9, 0, 4, 7, 0, 6, 0, 8},
                     {0, 5, 2, 8, 1, 9, 4, 0, 7},
                     {2, 0, 0, 0, 4, 8, 0, 0, 0},
                     {0, 0, 9, 0, 0, 0, 5, 0, 0},
                     {0, 0, 0, 7, 5, 0, 0, 0, 9},
                     {9, 0, 7, 3, 6, 4, 1, 8, 0},
                     {5, 0, 6, 0, 8, 1, 0, 7, 4},
                     {0, 8, 0, 0, 0, 0, 0, 0, 0}};

void game_randomlyPickFixCells(){

}

//void printMatrix(void* ptr, int row, int col){
//	int r, c;
//	int** matrix = (int**)ptr;
//
//	printf("----------------------------------\n");
//	for(r=1; r<10; ++r)
//	{
//		for(c=1; c<10; ++c)
//			printf("|%d", matrixSolver[r-1][r-1]);
//		printf("|\n");
//		if (r%3 == 0) printf("----------------------------------\n");
//	}
//}

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

/**
 * create empty board
 * use randomized backtracking to get random solve board
 * repeat fix cell H time
 */
void game_create(int rows, int cols ,int fixCell, int seed){
	//matrixSolver = (int *)calloc(rows * cols , sizeof(Cell));
	/*printMatrix(matrixSolver,cols,cols);*/
	//solver_randomizeBacktracking(matrixSolver,rows,cols);
	//game_randomlyPickFixCells();

	matrixSolve = createMatrix(rows,cols);
	matrixPlay=createMatrix(rows,cols);
	matrixfixed= createMatrix(rows, cols);
	printBoard(matrixPlay,  matrixfixed);
	solver_randomizeBacktracking(matrixSolve,rows,cols);
	game_randomlyPickFixCells();

}

//bool game_isGameFinish(){
//
//}

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

