#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"
#include "Game.h"
#include "main_aux.h"


int main ( int argc, char **argv ){

	int fixCell = 0;
	int seed = 0;
	char* command;
	int row = 3;
	int col = 3;

	fixCell = mainAux_getNumberOfFixCells();
	game_create(row,col,fixCell,seed);
	while(game_isGameFinish()==false) {
		command = mainAux_readCommand();
	}

	return 0;
}
