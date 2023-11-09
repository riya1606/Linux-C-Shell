#include "headers.h"

void pwd()
{
	char cwd[1024];
	getcwd(cwd, 1024);
	printf("%s\n", cwd);

}