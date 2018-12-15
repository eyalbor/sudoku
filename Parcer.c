
#include "Bool.h"
#include "ADT_Error.h"
#include "Parcer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void static strToLower(char* str){
	int i = 0;
	while(str[i]!='\0'){
		str[i] = tolower(str[i]);
		++i;
	}
}

void parser_parseCommand(char* str, Command* retCommand){
	char* tokens;
	tokens = strtok(str," ");
	if(tokens != NULL){
		strToLower(tokens);
		if(strcmp(tokens,"set")==0)
		{
			(*retCommand).func = SET;
			tokens = strtok(NULL," ");
			(*retCommand).x = atoi(tokens);
			tokens = strtok(NULL," ");
			(*retCommand).y = atoi(tokens);
			tokens = strtok(NULL," ");
			(*retCommand).z = atoi(tokens);
		} else if(strcmp(tokens,"hint")==0){
			(*retCommand).func = HINT;
			tokens = strtok(NULL," ");
			(*retCommand).x = atoi(tokens);
			tokens = strtok(NULL," ");
			(*retCommand).y = atoi(tokens);
		} else if(strcmp(tokens,"validate")==0){
			(*retCommand).func = VALIDATE;
		} else if(strcmp(tokens,"restart")==0){
			(*retCommand).func = RESTART;
		} else if(strcmp(tokens,"exit")==0){
			(*retCommand).func = EXIT;
		}
	}else{
		(*retCommand).func = NONE;
	}
}


