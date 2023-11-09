#include "headers.h"

void background(char **list, int cnt)
{
	int ret = 0;
	pid_t curr_pid = fork();
	CHILDPID = curr_pid;

	setpgid(0, 0);
	if (curr_pid < 0)
	{
		perror("Error: Background");
	}
	if (curr_pid == 0)
	{
		ret = execvp(list[0], list);
		//printf("ret in child = %d\n", ret );
		if (ret < 0)
		{
			printf("Invalid command: Check again!");
			kill(getpid(), SIGKILL);
			exit(0);
		}
		if (strcmp(list[0], "vim") == 0)
			kill(getpid(), 19);
	}
	else
	{
		//printf("hello\n");
		//printf("printing cnt from backgrouns: %d\n", cnt );
		//printf("ret in parent = %d\n", ret );
		//parent: Update Jobs
		job_cnt++;
		job_arr[job_cnt].pid = curr_pid;

		int k = 0;
		char var[100];
		for (int i = 0; i < cnt - 1; i++)
		{
			//printf("list[%d] = %s \n", i, list[i]);
			//printf("strlen of %s = %lu \n", list[i], strlen(list[i]));

			for (int j = 0; j < strlen(list[i]); j++)
			{
				var[k] = list[i][j];
				//printf("%c\n", var[k]);
				k++;

			}
			var[k] = ' ';
			k++;
		}

		var[k] = '\0';
		strcpy(job_arr[job_cnt].name, var);

		//strcpy(job_arr[job_cnt].name, list[0]);
		//printf("background full name  = %s\n", job_arr[job_cnt].name);
		printf("[%d] %d %s\n", job_cnt, job_arr[job_cnt].pid, job_arr[job_cnt].name);

		//wait(NULL);
	}
}