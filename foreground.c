#include "headers.h"

void foreground(char **list)
{
	pid_t curr_pid = fork();


	if (curr_pid == 0)
	{
		if (execvp(list[0], list) < 0)
		{
			printf("Invalid command: Check again!\n");
		}
		exit(0);
	}
	else
	{
		wait(NULL);
	}
}