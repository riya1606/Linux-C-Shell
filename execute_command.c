#include "headers.h"

void execute_command(char **list, char *home_dir, int cnt, char *cmd)
{

	//printf("in execute_command %d %d\n", STDIN_FILENO, STDOUT_FILENO );
	//printf("in execute_command printing in and out %d %d\n", in, out );
	//printf("in execute_command %d %d\n", STDIN_FILENO, STDOUT_FILENO );

	if (strcmp(list[0], "cd") == 0)
	{
		//printf("hello heloo\n");
		if (list[2] != NULL)
		{
			//cd can handle only two arguments and hence if list[2]!=NULL, too many arguments
			printf("cd: too many arguments\n");
		}
		else
		{
			if (cd_call(list, cmd, home_dir) == -1)
				printf("cd: no such file or directory: %s\n", list[1]);
		}
	}
	else if (strcmp(list[0], "pwd") == 0)
		pwd();

	else if (strcmp(list[0], "echo") == 0)
		echo_func(list);

	else if (strcmp(list[0], "ls") == 0)
	{
		//printf("cnt is %d\n", cnt );
		//printf("home_dir %s\n", home_dir );
		ls_call(list, cnt - 1, home_dir);
	}
	else if (strcmp(list[0], "pinfo") == 0)
	{
		pinfo_call(cnt - 1, list, home_dir);
	}
	else if (strcmp(list[0], "history") == 0)
	{
		if (list[1] == NULL)
			print_hist(10);
		else
			print_hist(atoi(list[1]));
	}

	else if (strcmp(list[0], "setenv") == 0)
	{
		//printf("%d\n", cnt - 1 );
		setenv_call(list, cnt - 1);
	}

	else if (strcmp(list[0], "unsetenv") == 0)
	{
		//printf("%d\n", cnt - 1);
		unsetenv_call(list, cnt - 1);
	}
	else if (strcmp(list[0], "quit") == 0)
	{
		printf("Exiting Shell\n");
		overkill();

		exit(EXIT_SUCCESS);
	}
	else if (strcmp(list[0], "overkill") == 0)
	{
		overkill();
	}
	else if (strcmp(list[0], "jobs") == 0)
		jobs_call();

	else if (strcmp(list[cnt - 2], "&") == 0)
	{
		char *new_list[100];
		int j = 0;
		//printf("cnt background %d\n", cnt);
		for (int i = 0; i < cnt - 2; i++)
		{
			//printf("hihihihi\n");
			new_list[j] = (char*)malloc(200 * sizeof(char));
			strcpy(new_list[j], list[i]);
			new_list[j][strlen(list[i]) ] = '\0';
			j++;
		}
		cnt--;
		/*for (int i = 0; i <= cnt - 2; i++)
		{
			//printf("new_list[%d] = %s\n", i, new_list[i] );
		}*/
		new_list[j] = NULL;
		//list[1]== & e.g. emacs &
		background(new_list, cnt);
	}
	else if (list[1] != NULL && strcmp(list[1], "&") == 0)
	{
		//printf("background seperate\n");
		char *new_list[100];
		int j = 0;
		//printf("cnt background %d\n", cnt);
		for (int i = 0; i <= cnt - 2; i++)
		{
			//printf("hihihihi\n");
			if (i == 1)
				continue;

			new_list[j] = (char*)malloc(200 * sizeof(char));
			strcpy(new_list[j], list[i]);
			new_list[j][strlen(list[i]) ] = '\0';
			j++;
		}
		cnt--;
		/*for (int i = 0; i <= cnt - 2; i++)
		{
			//printf("new_list[%d] = %s\n", i, new_list[i] );
		}*/
		new_list[j] = NULL;
		//list[1]== & e.g. emacs &
		background(new_list, cnt);
	}
	else
	{
		// emacs&
		char first_command_copy[1024];
		strcpy(first_command_copy, list[0]);
		if (strstr(first_command_copy, "&") != NULL)
		{
			//printf("background together\n");
			list[0][strlen(list[0]) - 1] = '\0';
			background(list, cnt);
		}
		else
		{
			//printf("foreground\n");
			foreground(list);
		}
	}


}
