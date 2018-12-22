#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"
#include "Solver.h"
#include "Game.h"

#include <stdlib.h>
#include <stdio.h>

int **matrixSolve, **matrixPlay, **matrixfixed;

void game_init(){
	matrixSolve = NULL;
	matrixPlay = NULL;
	matrixfixed = NULL;
}

void game_cleanmatrix(int** matrix){
	int i,j;
	for(i=0; i<9; i++){
		for (j=0;j<9;j++){
			if (matrix[i][j]!=0){
				matrix[i][j]=0;
			}
		}
	}
}

/* fill the matrix with fixed cells.  */
void game_randomlyPickFixCells(int fixCells){
	int i=0, x=0, y=0;

	for(i=0;i<fixCells;++i){
		while(1){
			/* choose index of a cell randomly.
			 * there was an comment on moodle that first we need to randomaize the column and than the row*/
			y = rand()%9;
			x = rand()%9;


			/* if chosen cell is not yet fixed apdate. */
			if(matrixPlay[x][y]==0){
				matrixPlay[x][y]=matrixSolve[x][y];
				matrixfixed[x][y]=matrixSolve[x][y];
				break;
			}
		}
	}
}

void rowSeparator() {
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
				matrix[j]=NULL;
				free(matrix[j]);
			}
			free(matrix);
			matrix=NULL;
			return NULL;
		}
	}
	return matrix;
}

void destroyMatrix(int** matrix){
	int i;
	for (i=0;i<9;i++)
	{
		free(matrix[i]);
		matrix[i]=NULL;
	}
	free(matrix);
	matrix=NULL;
}

/**
 * create empty board
 * use randomized backtracking to get random solved board
 * repeat fix cell H time to update the board with fixed values.
 */
void game_create(int rows, int cols ,int fixCell){

	if(matrixSolve!=NULL){
		destroyMatrix(matrixSolve);
		matrixSolve=NULL;
	}
	if(matrixPlay!=NULL){
		destroyMatrix(matrixPlay);
		matrixPlay=NULL;
	}
	if(matrixfixed!=NULL){
		destroyMatrix(matrixfixed);
		matrixfixed=NULL;
	}

	matrixSolve = game_createMatrix(rows,cols);
	if(matrixSolve!=NULL){
		matrixPlay = game_createMatrix(rows,cols);
		if(matrixPlay!=NULL){
			matrixfixed = game_createMatrix(rows, cols);
			if(matrixfixed!=NULL){
				solver_randomizeBacktracking(matrixSolve);
				game_randomlyPickFixCells(fixCell);
			} else{
				destroyMatrix(matrixPlay);
				destroyMatrix(matrixSolve);
				matrixSolve=NULL;
				matrixPlay=NULL;
			}
		} else{
			destroyMatrix(matrixSolve);
			matrixSolve=NULL;
		}
	}
}
void game_destroyGame(){
	destroyMatrix(matrixSolve);
	matrixSolve = NULL;
	destroyMatrix(matrixPlay);
	matrixPlay=NULL;
	destroyMatrix(matrixfixed);
	matrixfixed=NULL;
}

/*
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
 * check if the cell point (x,y) is fixed
 */
bool game_isCellFix(int x, int y){
	return matrixfixed[x][y]!=0?true:false;
}

bool game_setValue(int x, int y, int z){
	if(solver_is_legalValue(matrixPlay,x,y,z)==true){
		matrixPlay[x][y]=z;
	}else{
		return false;
	}
	return true;
}

int game_getValue(int x, int y){
	return matrixSolve[x][y];
}

/**
 * Assume x, y, z is valid
 */
ADTErr game_set(Command* command){
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

/* check if board can be solved  */
ADTErr  game_validate(){
	int** temp,i,j;
	/* create a new matrix and solve it without changing the current matrix  */
	temp=game_createMatrix(9,9);
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			temp[i][j]=matrixPlay[i][j];
		}
	}
	if(solver_determenistic_algo(temp,matrixSolve)==true){
		destroyMatrix(temp);
		return VALIDATION_PASSED;
	}
	destroyMatrix(temp);
	return VALIDATION_FAILED;
}


/*  get command from user and play */
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

