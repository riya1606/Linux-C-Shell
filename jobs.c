#include "headers.h"

void jobs_call()
{
	for (int i = 1; i <= job_cnt; i++)
	{

		printf("[%d] ", i );
		int pid = job_arr[i].pid;


		char command_status[10000];
		sprintf(command_status, "/proc/%d/status", pid);
		FILE* file = fopen(command_status, "r");
		//FILE* file = fopen(command_status, "r"); should check the result
		char line[256];
		for (int j = 1; j < 3; j++)
			fgets(line, sizeof(line), file);

		fgets(line, sizeof(line), file);
		{
			char buf[100];
			strcpy(buf, line);
			char *token1 = strtok(buf, ": \t\r\n\v\f");
			token1 = strtok(NULL, ": \t\r\n\v\f");

			if (strcmp(token1, "T"))
				printf("Stopped ");
			else
				printf("Running ");

			// note that fgets don't strip the terminating \n, checking its
			// presence would allow to handle lines longer that sizeof(line)
			// printf("%s", line);
		}

		printf("%s [%d] \n", job_arr[i].name, pid);



	}

}