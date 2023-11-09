#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void pinfo_defined(pid_t pid, char *home_dir)
{
	//if(cnt>1)
	//	perror("Too many arguments");
	if (pid == -1)
		pid = getpid();
//	printf("pid = %d\n",pid);
	char command_status[10000];
	sprintf(command_status, "/proc/%d/status", pid);

	printf("pid -- %d\n", pid);

	//fopen(file, O_RDONLY);


	/* should check that argc > 1 */
	FILE* file = fopen(command_status, "r"); /* should check the result */
	char line[256];
	for (int i = 1; i < 3; i++)
		fgets(line, sizeof(line), file);

	fgets(line, sizeof(line), file);
	{
		char buf[100];
		strcpy(buf, line);
		char *token1 = strtok(buf, ": \t\r\n\v\f"); token1 = strtok(NULL, ": \t\r\n\v\f");
		printf("Process Status -- %s\n", token1);
		/* note that fgets don't strip the terminating \n, checking its
		   presence would allow to handle lines longer that sizeof(line) */
		// printf("%s", line);
	}

	for (int i = 3; i < 17; i++)
		fgets(line, sizeof(line), file);

	fgets(line, sizeof(line), file);
	{
		char buf[100];
		strcpy(buf, line);
		char *token1 = strtok(buf, ": \t\r\n\v\f"); token1 = strtok(NULL, ": \t\r\n\v\f");

		/* note that fgets don't strip the terminating \n, checking its
		   presence would allow to handle lines longer that sizeof(line) */
		printf("memory --%s\n", token1);

	}

	char command_exe[10000];
	sprintf(command_exe, "/proc/%d/exe", pid);
	char exe_link[100000];
	int link_len = readlink(command_exe, exe_link, sizeof(exe_link));
	//printf("Executable Path -- %s\n",exe_link);

	//Checking if home_dir is present in executable path
	char *rel_path = strstr(exe_link, home_dir);
	if (rel_path != NULL)
	{
		rel_path += strlen(home_dir);
		printf("Executable Path -- ~%s\n", rel_path);
	}
	else
	{
		printf("Executable Path -- %s\n", exe_link);
	}


	/* may check feof here to make a difference between eof and io failure -- network
	   timeout for instance */

	fclose(file);

	//` return 0;
	//char *cwd[1024];
	//getcwd(cwd, sizeof(cwd));
	//printf("%s\n", cwd);

}

void pinfo_call(int cnt, char **list, char *home_dir)
{
	pid_t pid;
	if (cnt == 1)
		pid = -1;
	else
		pid = atoi(list[1]);
	pinfo_defined(pid, home_dir);


}
