
#include <stdio.h>
#include <stdlib.h>
#include "ADT_Error.h"

 void HandleErr(ADTErr errNum)
{
	 char* ad[]=
	{
		/* General ADT Errors */
		"ERR_OK",
		"ERR_GENERAL",
		"ERR_NOT_INITIALIZED",
		"ERR_ALLOCATION_FAILED",
		"ERR_REALLOCATION_FAILED",
		"ERR_UNDERFLOW",
		"ERR_OVERFLOW",
		"ERR_WRONG_INDEX",
		/* String Errors */
		"cell is fixed",
		"value is invalid",
		"HINT",
		"PUZZLE_SOLVED",
		"Validation passed: board is solvable",
		"Validation failed: board is unsolvable",
		"invalid command"

	};
	if(errNum==VALIDATION_PASSED){
		printf("%s\n", ad[errNum]);
	}
	else{
		printf("Error: %s\n", ad[errNum]);
	}
}

