#ifndef ADTERROR_H_
#define ADTERROR_H_

typedef enum
{
    /* General ADT Errors */
    ERR_OK                            =0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,

    /* String Errors */
	CELL_FIX,
	VALUE_INVALID,
	HINT_ERR,
	PUZZLE_SOLVED,
	VALIDATION_PASSED
} ADTErr;

/**
 * HandleErr
 * print the error
 * input: ADTErr error
 */
void HandleErr(ADTErr errNum);

#endif /*ADTERROR_H_*/
