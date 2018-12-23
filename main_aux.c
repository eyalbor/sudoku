#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"
#include "Game.h"
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
		if(isNumber(argv[1])){
			seedStr = argv[1];
			seed = atoi(seedStr);
			/*printf("%d",seed);*/
		}
		else{
			return -1;
		}
	}
	return seed;
}

/**
 * return number between 0-80. if get EOF return -1
 */
int mainAux_getNumberOfFixCells(){
	int fix = 0, scanRet=0;
	int c =0;

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
	while ((c = getchar()) != '\n' && c != EOF) { }
	return fix;
}

bool mainAux_readCommand(char* command){

	fseek(stdin,0,SEEK_END);

	if (NULL == fgets(command,100,stdin)){

		return false;
	}
	return true;
}

void mainAux_printBoard(){
	game_printBoard();
}

void mainAux_printExit(){
	printf("Exiting...\n");
}

void mainAux_printError(ADTErr err){
	HandleErr(err);
}

void main_Aux_printHint(int z){
	printf("Hint: set cell to %d\n",z);
}
