#ifndef GAME_H_
#define GAME_H_

typedef struct cell_t{
	int value;
	bool isFix;
} Cell;

void 	game_create(int row, int col,int fixCell, int seed);
void 	game_destroyGame();
ADTErr 	game_playTurn(Command* command);
void 	game_randomlyPickFixCells();
bool 	game_isGameFinish(int rows, int cols);

#endif
