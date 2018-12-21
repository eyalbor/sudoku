#ifndef GAME_H_
#define GAME_H_

/*typedef struct cell_t{
	int value;
	bool isFix;
} Cell;
*/


/** game_init
 * Output: we have created 3 double pointers for matrixes.this function updates pointers of matrixes into NULL
 */
void	game_init();
<<<<<<< HEAD
void 	game_create(int row, int col,int fixCell);
=======


/** game_create
 * Input:
 * 		int row: size of rows in a matrix.
 * 		int col: size of columns in a matrix.
 * 		int fixcell: how many fixed cells we received from the user to put into out matrix.
 * 		int seed: the seed we receive in our program.
 * Output:
 * 		checks if matrixes are already exists in the program and destroy.
 * 		otherwise creates 3 double sized arrays(our matrixes): matrixPlay, matrixSolve, matrixFixed.
 * 		updates matrixFixed to be a randomized legal puzzle. updates matrixPlay and matrixSolve with fixed cells.
 */
void 	game_create(int row, int col,int fixCell, int seed);

/** game_destroyGame
 * Output: destroy all matrixes in the program and free memory.
 */
>>>>>>> master
void 	game_destroyGame();

/** game_playTurn
 * Input: Command* command : command received from the user.
 * return: ADTErr. check which command entered by user : set, validate or hint and calls the suitable function.
 * return the error occurred if any.
 */
ADTErr 	game_playTurn(Command* command);

/**game_randomlyPickFixCells
 * Input: int number : how many fixed cells the user wants in the puzzle.
 * Output: update the fixed matrix and the play matrix with the number of fixed cells the user entered.
 */
void 	game_randomlyPickFixCells(int number);

/** game_isGameFinish
 * Input:
 * 		 int rows : how many rows in a matrix
 * 		 int cols : how many columns in a matrix
 * return: bool true or false.  if the matrix is full and all legal are valid return true otherwise false.
 */
bool 	game_isGameFinish(int rows, int cols);

/** game_printBoard
 * Output: prints the matrix matrixPlay.
 */
void 	game_printBoard();

#endif
