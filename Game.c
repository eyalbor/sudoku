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

void game_destroyGame(){

}


/*
 * added by nadine
 * checks if board is full
 * the function iterates over the matrix and check:
 * if not all cells are filled- it means the game is unfinished.
 * if one cell contains an illegal value game is not over.
 */
bool game_isGameFinish(){
	int i,j,value;
	for(i=0; i<rows; i++)
	{
		for(j=0; j<cols;j++)
		{
			value=matrixPlay[i][j];
			if(value==0)
			{
				return false;
			}
			if(solver_is_legalvalue(matrixPlay, i, j, value)==0)
			{
				return false;
			}
		}
	}
	return true;
}

/**
 * check if the cell point (x,y) is fix
 */
bool static game_isCellFix(int x, int y){
	return true;
}

bool static game_setValue(int x, int y, int z){
	return true;
}

int static game_getValue(int z, int y){
	return 0;
}

/**
 * Assume x, y, z is valid
 */
ADTErr static game_set(Command* command){
	if(game_isCellFix(command->x,command->y))
		return CELL_FIX;
	if(game_setValue(command->x,command->y, command->z)){
		return VALUE_INVALID;
	}
	return ERR_OK;
}

ADTErr  game_hint(Command* command){
	int z = game_getValue(command->x,command->y);
	command->z = z;
	return HINT_ERR;
}

ADTErr static game_validate(){
	return ERR_OK;
}

ADTErr game_playTurn(Command* command){
	ADTErr ret = ERR_OK;
	FUNC func = command->func;
	if(func==SET){
		ret = game_set(command);
	}
	else if(func==HINT){
		ret = game_hint(command);
	}
	else if(func==VALIDATE){
		ret = game_validate();
	}
	return ret;
}

