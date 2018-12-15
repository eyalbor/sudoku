#ifndef PARCER_H_
#define PARCER_H_

typedef enum {
	SET = 0,
	HINT,
	VALIDATE = 2,
	RESTART,
	EXIT,
	NONE
} FUNC;

typedef struct command_t{
	FUNC func;
	int x;
	int y;
	int z;
} Command;

/** parser_parseCommand
 * Input: chat* str - command string,
 * 		  Commant Ptr to be filled inside the function
 * Output:
 */
void parser_parseCommand(char* str, Command* retCommand);

#endif
