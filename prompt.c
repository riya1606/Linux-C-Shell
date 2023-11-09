
#include "headers.h"
#include "prompt.h"
char home_dir[1024];


char* get_homedir()
{
	//Assuming that the max length of the home dir = 1024
	getcwd(home_dir, 1024);
	return home_dir;
}

void prompt()
{
	//Assuming that the max length of the HOSTNAME and USERNAME dir = 1024
	char HOSTNAME[1024], USERNAME[1024];
	gethostname(HOSTNAME, sizeof(HOSTNAME));
	getlogin_r(USERNAME, sizeof(USERNAME));
	color_reset();

	//printing USERNAME and HOSTNAME in boldgreen colour
	bold_green();
	printf("<%s@", USERNAME);
	printf("%s:", HOSTNAME);
	color_reset();

	//Finding cur dir in each prompt and comparing it with home directory
	char curr_dir[1024];
	getcwd(curr_dir, 1024);
	bold_cyan();
	int cmp = strcmp(home_dir, curr_dir);
	//printf("strcmp = %d", cmp);
	//cur_dir == home_dir, print ~
	if (cmp == 0)
	{
		printf("~>");
	}
	//home_dir>cur_dir in length, print complete path
	else if (cmp > 0)
	{
		printf(" %s>", curr_dir);
	}

	//home_dir<Cur_dir, so print~ and then further path using while loop
	else if (cmp < 0)
	{
		printf("~");
		int i = strlen(home_dir);
		while (curr_dir[i] != '\0')
		{
			printf("%c", curr_dir[i]);
			i++;
		}
		printf(">");
	}
	color_reset();
}

void bold_green () {
	printf("\033[1;32m");
}

void bold_cyan() {
	printf("\033[1;36m");
}

void color_reset () {
	printf("\033[0m");
}
void red () {
	printf("\033[0;31m");
}
