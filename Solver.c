#include "Bool.h"
#include "Solver.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

bool valid_array_number[9][9][9] = {false};


int solver_createlegalvalue(int**matrixSolve,int row, int col){
	int number,count;
	for (number = 1; number< 10; number++)
	{
		if(solver_is_legalValue(matrixSolve,row,col,number))
		{
			valid_array_number[row][col][number-1] = true;
			count++;
		}
	}
	return count;
}

int choose_Valuefrom3Dmatrix(int count,int x, int y){
	int randNum,i;

	randNum = (rand()%count)+1;
	for(i=0;i<9;i++){
		if(valid_array_number[x][y][i]==true)
		{
			randNum--;
			if(randNum==0)
			{
				return i;
			}
		}
	}
	return -1;
}

void swap(int* randArr, int index1, int index2){
	int temp = randArr[index1];
	randArr[index1] = randArr[index2];
	randArr[index2] = temp;
}


void randomizeArray(int* randArr,int size){
	int i, index1, index2;
	for(i=0;i<size;i++){
		randArr[i]=i+1;
	}
	for(i=0;i<100;i++){
		index1 = rand()%9;
		index2 = rand()%9;
		swap(randArr,index1, index2);
	}
}


bool solver_randomizeBacktracking(int** matrixSolve){
	int randArr[9];
	int row, col, number;
	randomizeArray(randArr, 9);

	for (row = 0; row < 9; row++)
	{
		for (col = 0; col < 9; col++)
		{
			/* if cell is empty check if it can be filled*/
			if (matrixSolve[row][col] == 0)
			{
				for (number = 0; number< 9; number++)
				{
					if (solver_is_legalValue(matrixSolve, row, col, randArr[number]) == 1)
					{
						/* if the cell is empty and the value is legal fill the cell  */
						matrixSolve[row][col] = randArr[number];
						/* recursive call. check the next cell. the previous cells are not empty anymore
						 * we put a value with the previous calls */
						if (solver_randomizeBacktracking(matrixSolve) == 1)
						{
							return true;
						}
						else
						/* if the call return 0 delete the element and continue to check the next number*/
						{
							matrixSolve[row][col] = 0;
						}
					}
				}
				/*  if no number is legal then delete the cell */
				if (number == 9)
				{
					matrixSolve[row][col] = 0;
					return false;
				}
			}
			else if ((col == 8) && (row == 8) && (solver_is_legalValue(matrixSolve, 8, 8,matrixSolve[8][8])==1))
			{
				return true;
			}
		}
	}
	return false;
}


/* added by nadin*/
/*
 * this function checks if the value entered in a specific cell is a valid one. if there is the same value in the same row
 * the function returns 0 otherwise it is a legal value and the function returns 1.
 */
bool check_row(int **matrixPlay, int row, int col, int checked_value){

	int i;
	for (i = 0; i< 9; i++)
	{
		if (i != col)
		{
			if (matrixPlay[row][i] == checked_value)
			{
				return false;
			}
		}
	}
	return true;
}
/* added by nadin
 *
 * this function checks if the value entered in a specific cell is a valid one. if there is the same value in the same colomn
 * the function returns 0 otherwise it is a legal value and the function returns 1.
 *
 */
bool check_col(int **matrixPlay, int row, int col, int checked_value){
	int i;
	for (i = 0; i< 9; i++)
	{
		if (i != row)
		{
			if (matrixPlay[i][col] == checked_value)
			{
				return false;
			}
		}
	}
	return true;
}

/*
 * added by nadin
 * checks if the number exists in the same block. this function divides the matrix into 9 blocks.
 * first it checks for which block the index belongs and after it iterates over the 9 elements.
 * it returns 1 if value is valid
 *
 *
 */

bool checkBlock(int **matrixPlay, int x, int y, int checked_value) {
	int a, b, c, d;
	a = (x / 3) * 3;/* it tells in which block the index is. 0-2 are in block 0. 3-5 in block 2 which start at index 3 and 6-8 in block 3
	that start in index 6. */
	b = (y / 3) * 3; /* the same with the col*/
	for (c = 0; c < 3; c++)
	{ /*  iterates over the elements in the block */
		for (d = 0; d < 3; d++)
		{
			if ( !((a+c==x) &&(b+d==y)) )
			{
				if (matrixPlay[a + c][b + d] == checked_value)
				{
					return false;
				}
			}
		}
	}
	return true;

}
/* return whether the value is valid- different from all values in the same row block and column   */

bool solver_is_legalValue(int **matrixPlay, int x, int y, int checked_value){

	if(checked_value==0)
	{
		return true;
	}
	if(checkBlock(matrixPlay, x, y, checked_value)==0)
	{
		return false;
	}
	if(check_row(matrixPlay, x, y, checked_value)==0)
	{
		return false;
	}
	if(check_col(matrixPlay, x, y, checked_value)==0)
	{
		return false;
	}
	return true;
}

/* this function receives a board in a current position and checks if there is a solution.
 * incase there is, it updates the solved board to the new solution and returns 1 */

int solver_determenistic_algo(int **matrixPlay,int **matrixSolve){

	int row, col, number;
	for (row = 0; row < 9; row++)
	{
		for (col = 0; col < 9; col++)
		{
			/* if cell is empty check if it can be filled*/
			if (matrixPlay[row][col] == 0)
			{
				for (number = 1; number< 10; number++)
				{
					if (solver_is_legalValue(matrixPlay, row, col, number) == 1)
					{
						/* if the cell is empty and the value is legal fill the cell  */
						matrixPlay[row][col] = number;
						/* recursive call. check the next cell. the previous cells are not empty anymore
						 * we put a value with the previous calls */
						if (solver_determenistic_algo(matrixPlay, matrixSolve) == 1)
						{
							if(row==8 && col==8){
								memcpy(matrixSolve, matrixPlay, 81);
							}
							return 1;
						}
						else
						/* if the call return 0 delete the element and continue to check the next number*/
						{
							matrixPlay[row][col] = 0;
						}
					}
				}
				/*  if no number is legal then delete the cell */
				if (number == 10)
				{
					matrixPlay[row][col] = 0;
					return 0;
				}
			}
			else if ((col == 8) && (row == 8) && (solver_is_legalValue(matrixPlay, 8, 8,matrixPlay[8][8])==1))
			{
				memcpy(matrixSolve, matrixPlay, 82);
				return 1;
			}
		}
	}

	return 0;
}
