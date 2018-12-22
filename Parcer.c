
#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


void strToLower(char* str){
	int i = 0;
	while(str[i]!='\0'){
		str[i] = tolower(str[i]);
		++i;
	}
}

bool isNumber(char* input){
	int i;
	int ln;

	ln = strlen(input) - 1;
	/* Ensure that input is a number */
	for(i = 0; i < ln; i++){
	    if( !isdigit(input[i]) ){
	        return false;
	    }
	}
	return true;
}


ADTErr parser_parseCommand(char* str, Command* retCommand){
	char* tokens;
	char delimit[]=" \t\r\v\f\n";

	tokens = strtok(str,delimit);
	if(tokens != NULL){
		strToLower(tokens);
		if(strcmp(tokens,"set")==0)
		{/* y is row , x is column */
			(*retCommand).func = SET;
			tokens = strtok(NULL,delimit);
			if(tokens!=NULL){
				if(isNumber(tokens)==false) {return INVALID_COMMAND;}
				(*retCommand).y = atoi(tokens)-1;
				tokens = strtok(NULL,delimit);
				if(tokens!=NULL){
					if(isNumber(tokens)==false) {return INVALID_COMMAND;}
					(*retCommand).x = atoi(tokens)-1;
					tokens = strtok(NULL,delimit);
					if(tokens!=NULL){
						if(isNumber(tokens)==false) {return INVALID_COMMAND;}
								;}
						(*retCommand).z = atoi(tokens);
						return ERR_OK;
					}
				}
			} else if(strcmp(tokens,"hint")==0){
				(*retCommand).func = HINT;
				tokens = strtok(NULL,delimit);
				if(tokens!=NULL){
					if(isNumber(tokens)==false) {return ERR_OK;}
					(*retCommand).y = atoi(tokens)-1;
					tokens = strtok(NULL,delimit);
					if(tokens!=NULL){
						if(isNumber(tokens)==false) {return ERR_OK;}
						(*retCommand).x = atoi(tokens)-1;
						return ERR_OK;
					}
				}
			} else if(strcmp(tokens,"validate\n")==0){
				(*retCommand).func = VALIDATE;
				return ERR_OK;
			} else if(strcmp(tokens,"restart\n")==0){
				(*retCommand).func = RESTART;
				return ERR_OK;
			} else if(strcmp(tokens,"exit\n")==0){
				(*retCommand).func = EXIT;
				return ERR_OK;
			}
	}
	return INVALID_COMMAND;
}




