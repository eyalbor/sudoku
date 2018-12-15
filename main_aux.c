#include "Bool.h"
#include <stdio.h>
#include <stdlib.h>

int mainAux_getNumberOfFixCells(){
	int fixed_cells;
	printf("Please enter the number of cells to fill [0-80]:\n");
	if (scanf("%d", &fixed_cells) != 1)
	{
		printf("Error: scan has failed. Exiting\n");
		return -1;
	}
	while ((fixed_cells >80 || fixed_cells < 0))
	{
		printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
		printf("Please enter the number of cells to fill [0-80]:\n");
		scanf("%d", &fixed_cells);
	}
	return fixed_cells;
}

char* mainAux_readCommand(){
	//scanf
	//strtok
	//Command = parser_checkValidCommand
	//game_playTurn(command)
	return NULL;
}

/* nadin*/
void rowSeparator() {
	int i;
	for (i = 0; i < 34; i++) {
		printf("-");
	}
	printf("\n");
}

/*nadin: print the current position of the board */

void printBoard( int **matrixPlay, int **matrixfixed){
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
			}else if(matrixfixed[i][j]==0 && matrixPlay[i][j]!=0)
			{
				printf(" %d ",matrixPlay[i][j]);
			}else
			{
				printf("   ");
			}
		}printf("|\n");
	}rowSeparator();
}
