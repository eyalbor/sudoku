#include "Bool.h"
#include "Solver.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/* last one */
/*bool valid_array_number[9][9][9] = {false};*/


void swap(int* randArr, int index1, int index2){
	int temp = randArr[index1];
	randArr[index1] = randArr[index2];
	randArr[index2] = temp;
}

bool solver_randomizeBacktracking(int** matrixSolve){
	int randArr[9]={0};
	int i, j, value,n, countof_Legalvalues = 0, randomized_index;
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				if (matrixSolve[i][j] == 0)
				{
					for (value = 1; value < 10; value++)
					{ /*filling the array with legal values.*/
						if (solver_is_legalValue(matrixSolve, i, j, value) == 1)
						{
							randArr[countof_Legalvalues] = value;
							countof_Legalvalues++;
						}

					}
					while (countof_Legalvalues > 1) { /*randomly picking and recursively calling the function.
						we have several options and we want to check if one of them is legal solution*/

							randomized_index = rand() % countof_Legalvalues;
							/* as the array with the legal indexes is filled from the first cell it ensures that the size is the
							 * count of legal values and the array is empty from the end until 9 minus count of legal values.
							 * choose randomly an index from legal values  */
							matrixSolve[i][j] = randArr[randomized_index];
							for (n=randomized_index; n<countof_Legalvalues;n++){
								swap(randArr,n,n+1);
							}
							countof_Legalvalues--; /*now we have one less valid value.*/
							if (solver_randomizeBacktracking(matrixSolve) == 1)
							{
								return true;
							} else
							{
								matrixSolve[i][j] = 0;/*delete the value and try again recursivly to check the other options  */
							}
						}

					 if (countof_Legalvalues == 1)
					{ /*no need for choosing a value in randomized way as only one is remain.*/
						matrixSolve[i][j] = randArr[0];
						countof_Legalvalues=0;
						if (solver_randomizeBacktracking(matrixSolve) == 1)
						{/* after putting the remained value check if matrix can be solved */
							return true;
						}else{
							matrixSolve[i][j]=0;

							}
					}
					if (countof_Legalvalues == 0)
					{ /*all values failed for this cell.*/
						matrixSolve[i][j]=0;
						return false; /* no value remain is a valid one so no  */
					}


				} else if ((i == 8) && (j == 8)&& (solver_is_legalValue(matrixSolve, 8, 8, matrixSolve[i][j]) == 1)) {

					return true;
				}
			}
		}
	return false;
}


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

 /*
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



void copy_boards(int** old, int**new,int size){
	int i;
	for(i=0; i<size;i++){
		memcpy(new[i], old[i],size*size);
	}
}

/* this function receives a board in a current position and checks if there is a solution.
 * incase there is, it updates the solved board to the new solution and returns 1 */

bool solver_determenistic_algo(int **matrixPlay,int **matrixSolve){

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
								copy_boards(matrixSolve,matrixPlay,9);
							}
							return true;
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
					return false;
				}
			}
			else if ((col == 8) && (row == 8) && (solver_is_legalValue(matrixPlay, 8, 8,matrixPlay[8][8])==1))
			{
				copy_boards(matrixSolve,matrixPlay,9);
				return true;
			}
		}
	}

	return 0;
}
