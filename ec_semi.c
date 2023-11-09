#include "headers.h"
char *cmd[1000];

char** extract_semicolon(char *input, int *cnt_semi)
{

	cmd[0] = strtok(input, ";"); //separating the commands
	//(*cnt_semi) = (*cnt_semi) + 1;
	long long int i = 0, j = 0;
	while (cmd[i] != NULL)
	{	//printf("hi\n");
		//(*cnt_semi) = (*cnt_semi) + 1;
		i++;
		cmd[i] = strtok(NULL, ";");
	}


	return cmd;

}