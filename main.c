#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"
#include "Game.h"
#include "main_aux.h"

/* nadine test2*/
int main ( int argc, char **argv ){

	int fixCell = 0;
	int seed = 0;
	char* command;
	int row = 3;
	int col = 3;

	char* s = "nadin push";

	seed = mainAux_getSeed(argc,argv);
	fixCell = mainAux_getNumberOfFixCells();
	if(fixCell==-1){
		printf("Exiting...\n");
		return 0;
	}
	game_create(row,col,fixCell,seed);
//	while(game_isGameFinish()==false) {
//		command = mainAux_readCommand();
//	}

	return 0;
}
