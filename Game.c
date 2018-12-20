#include "Bool.h"
#include "Parcer.h"
#include "ADT_Error.h"
#include "Solver.h"
#include "Game.h"

#include <stdlib.h>
#include <stdio.h>

int **matrixSolve, **matrixPlay, **matrixfixed;

void	game_init(){
	matrixSolve = NULL;
	matrixPlay = NULL;
	matrixfixed = NULL;
}

void game_randomlyPickFixCells(int fixCells){
	int i, x, y;
	for(i=0;i<fixCells;++i){
		while(1){
			x = rand()%9;
			y = rand()%9;
			if(matrixPlay[x][y]==0){
				matrixPlay[x][y]=matrixSolve[x][y];
				matrixfixed[x][y]=matrixSolve[x][y];
				break;
			}
		}
	}
}

/* nadin*/
void static rowSeparator() {
	int i;
	for (i = 0; i < 34; i++) {
		printf("-");
	}
	printf("\n");
}


void game_printBoard(){
	int i,j;
	for(i=0; i<9; i++)
	{
		/*every 3 rows we will print a line*/
		if(i % 3 == 0)
		{
			rowSeparator();
		}
		for(j=0;j<9;j++)
		{
			/*every 3 col we will print a line*/
			if(j % 3 == 0)
			{
				printf("| ");
			}
			if(matrixfixed[i][j]!=0)
			{
				printf(".%d ",matrixPlay[i][j]);
			}
			else if(matrixfixed[i][j]==0 && matrixPlay[i][j]!=0)
			{
				printf(" %d ",matrixPlay[i][j]);
			}
			else
			{
				printf("   ");
			}
		}printf("|\n");
	}
	rowSeparator();
}

/*nadin- create the matrix  */
int **game_createMatrix(int rows, int col) {
	int **matrix, i,j;
	matrix = (int**)calloc(rows, sizeof(int *));
	if (matrix == NULL) {
		return NULL;
	}
	for (i = 0; i < 9; i++) {
		matrix[i] = calloc(col, sizeof(int));
		if (matrix[i] == NULL) {
			for(j=i-1 ; j>=0 ; j--){
				free(matrix[j]);
			}
			return NULL;
		}
	}
	return matrix;
}

void static destroyMatrix(int** matrix){
	int i;
	for (i=0;i<9;i++)
	{
		free(matrix[i]);
	}
	free(matrix);
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

	if(matrixSolve!=NULL){
		destroyMatrix(matrixSolve);
	}
	if(matrixPlay!=NULL){
		destroyMatrix(matrixPlay);
	}
	if(matrixfixed!=NULL){
		destroyMatrix(matrixfixed);
	}

	matrixSolve = game_createMatrix(rows,cols);
	if(matrixSolve!=NULL){
		matrixPlay = game_createMatrix(rows,cols);
		if(matrixPlay!=NULL){
			matrixfixed = game_createMatrix(rows, cols);
			if(matrixfixed!=NULL){
				solver_randomizeBacktracking(matrixSolve);
				//solver_determenistic_algo( matrixPlay,matrixSolve);
				//printBoard(matrixPlay,  matrixSolve);
				//printBoard(matrixSolve,  matrix_try);
				game_randomlyPickFixCells(fixCell);
				//printBoard(matrixPlay,  matrixfixed);
			} else{
				destroyMatrix(matrixPlay);
				destroyMatrix(matrixSolve);
			}
		} else{
			destroyMatrix(matrixSolve);
		}
	}
}

void game_destroyGame(){
	destroyMatrix(matrixSolve);
	destroyMatrix(matrixPlay);
	destroyMatrix(matrixfixed);
}

/*
 * added by nadine
 * checks if board is full
 * the function iterates over the matrix and check:
 * if not all cells are filled- it means the game is unfinished.
 * if one cell contains an illegal value game is not over.
 */
bool game_isGameFinish(int rows, int cols){
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
			if(solver_is_legalValue(matrixPlay, i, j, value)==false)
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
	return matrixfixed[x][y]!=0?true:false;
}

bool static game_setValue(int x, int y, int z){
	if(solver_is_legalValue(matrixPlay,x,y,z)==true){
		matrixPlay[x][y]=z;
	}else{
		return false;
	}
	return true;
}

int static game_getValue(int x, int y){
	return matrixSolve[x][y];
}

/**
 * Assume x, y, z is valid
 */
ADTErr static game_set(Command* command){
	if(game_isCellFix(command->x,command->y))
		return CELL_FIX;
	if(!game_setValue(command->x,command->y, command->z)){
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
	if(solver_determenistic_algo(matrixPlay,matrixSolve)==true){
		//success
		return VALIDATION_PASSED;
	}
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

