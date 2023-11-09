#include "headers.h"

void echo_func(char **list)
{
	int i = 1;
	while (list[i] != NULL)
	{
		printf("%s ", list[i]);
		i++;
	}
	printf("\n");
}