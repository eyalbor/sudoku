#ifndef GAME_H_
#define GAME_H_

typedef struct cell_t{
	int value;
	bool isFix;
} Cell;

void 	game_create(int row, int col,int fixCell, int seed);
ADTErr 	game_playTurn(Command command);
void 	game_randomlyPickFixCells();
bool 	game_isGameFinish();
ADTErr 	game_set();
ADTErr 	game_hint();
ADTErr 	game_validate();
void 	printMatrix(void* matrix, int row, int col);

#endif
