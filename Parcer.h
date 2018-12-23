/*
 * Parcer.h
 *
 *  Created on: Dec 11, 2018
 *      Author: eyal & nadin
 */

#ifndef PARCER_H_
#define PARCER_H_

typedef enum {
	SET = 0,
	HINT,
	VALIDATE = 2,
	RESTART,
	EXIT
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
 * Output: ADTErr ERR_OK or INVALID_COMMAND
 */
ADTErr parser_parseCommand(char* str, Command* retCommand);

/**
 * isNumber
 * Input: char* str
 * Output: true if the str is number else false
 */
bool isNumber(char* str);

#endif
