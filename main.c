#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"
#include "Game.h"
#include "main_aux.h"

#include <stdio.h>
#include <time.h>

int main ( int argc, char **argv ){

	ADTErr err;
	int fixCell = 0;
	int seed = 0;
	char commandStr[1024];
	int row = 9;
	int col = 9;
	Command command;

	seed = mainAux_getSeed(argc,argv);
	srand(seed);

	GAME:{
		fixCell = mainAux_getNumberOfFixCells();
		if(fixCell==-1){
			printf("Exiting...\n");
			return 0;
		}

		game_create(row,col,fixCell,seed);

		while(game_isGameFinish(row,col)==false) {
			mainAux_printBoard();
			//TODO delete
			printf("print command\n");
			//
			if(mainAux_readCommand(commandStr) == true){
				parser_parseCommand(commandStr, &command);
				if(command.func!=NONE){
					if( command.func == EXIT){
						mainAux_printExit();
						//TO-DO
						game_destroyGame();
						exit(0);
					}
					else if(command.func == RESTART){
						game_destroyGame();
						goto GAME;
					}
					else {
						err = game_playTurn(&command);
						if(err==HINT_ERR){
							main_Aux_printHint(command.z);
						}
						else if(err!=ERR_OK){
							mainAux_printError(err);
						}
					}
				}
			}
		}
		//TO-DO printf game finish
	}

	game_destroyGame();
	return 0;
}
