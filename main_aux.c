#include "Bool.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
	#define DO_ASSERT(x) assert(x)
	#define PRINT_MSG(msg)	printf("%s(%d): %s \n", __FILE__,__LINE__,__FUNCTION__,__TIME__,msg)
#else
	#define DO_ASSERT(x) ()
	#define PRINT_MSG(msg)
#endif

int mainAux_getSeed(int argc, char** argv){
	int seed = 0;
	char* seedStr = NULL;

	if(argc == 2){
		seedStr = argv[1];
		PRINT_MSG(seedStr);
		seed = atoi(seedStr);
	}
	return seed;
}

/**
 * return number between 0-80. if get EOF return -1
 */
int mainAux_getNumberOfFixCells(){
	int fix = 0, scanRet;

	printf("Please enter the number of cells to fill [0-80]:\n");
	while(1){
		scanRet = scanf("%d",&fix);
		if(scanRet==EOF){
			fix=-1;
			break;
		}
		if(fix>=0 && fix<=80){
			break;
		}
		printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
	}
	return fix;
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

void printBoard(int **matrixPlay, int **matrixfixed){
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
