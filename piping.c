#include "headers.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void execute_command_pipe(char **list, char *home_dir, int cnt, char *cmd);
int cmd_cnt_in_pipe = 0;

int piping(char* cmd, char *home_dir)
{
	int std_in_saved = dup(0);
	int std_out_saved = dup(1);
	//std_in_saved = dup(STDIN_FILENO);
	//printf("hi2\n");
	//counting no. of pipes
	int pipe_cnt = 0;
	for (int i = 0; i < strlen(cmd); i++)
	{
		if (cmd[i] == '|')
			pipe_cnt++;
	}
	if (pipe_cnt == 0)
		return -1;

	//strtok of piped command and solve tokens
	char *pipe_cmd_arr[100];
	//printf("hi3\n");
	pipe_cmd_arr[0] = strtok(cmd, "|"); //separating the commands
	long long int i = 0, j = 0;
	while (pipe_cmd_arr[i] != NULL)
	{
		i++;
		pipe_cmd_arr[i] = strtok(NULL, "|");
	}


	int fd[2];
	int pipe_input = 0;
	pid_t pid;


	for (int j = 0; pipe_cmd_arr[j] != NULL; j++)
	{

		if (j == 0)
		{
			char input_copy[1024];
			strcpy(input_copy, pipe_cmd_arr[j]);
			char *input_file =  strstr(input_copy, "<");
			if (input_file != NULL)
			{
				char *input_file_name;
				input_file_name = strtok(input_file + 1, " \t\r\n\v\f");
				int fd_input = open(input_file_name, O_RDONLY);
				dup2(fd_input, 0);
				char **list;
				cmd_cnt_in_pipe = 0;
				list = extract_command(pipe_cmd_arr[j], &cmd_cnt_in_pipe);


				pipe(fd);
				pid = fork();
				if (pid == 0)
				{
					//dup2(pipe_input , 0);
					if (pipe_cmd_arr[j + 1] != NULL)
						dup2(fd[1], 1);
					close(fd[0]);
					//printf("executing command %s in child\n", pipe_cmd_arr[j]);
					execute_command_pipe(list, home_dir, cmd_cnt_in_pipe, pipe_cmd_arr[j]);
					exit(2);
				}
				else
				{

					wait(NULL);
					close(fd[1]);
					pipe_input = fd[0];
				}

				continue;
			}


		}


		else if (pipe_cmd_arr[j + 1] == NULL)
		{
			char output_copy_1[1024]; //to check append
			char output_copy_2[1024]; //to check normal
			strcpy(output_copy_1, pipe_cmd_arr[j]);
			strcpy(output_copy_2, pipe_cmd_arr[j]);
			char *output_file_append =  strstr(output_copy_1, ">>");
			char *output_file_normal =  strstr(output_copy_2, ">");
			if (output_file_append != NULL && output_file_normal != NULL)
			{
				//printf("hello 123\n");
				char *output_file_name;
				output_file_name = strtok(output_file_append + 2, " \t\r\n\v\f");
				int fd_output = open(output_file_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
				//dup2(fd_output, 0);
				char **list;
				cmd_cnt_in_pipe = 0;
				list = extract_command(pipe_cmd_arr[j], &cmd_cnt_in_pipe);

				pipe(fd);
				pid = fork();
				if (pid == 0)
				{
					dup2(pipe_input , 0);
					//if (pipe_cmd_arr[j + 1] != NULL)
					//	dup2(fd[1], 1);
					dup2(fd_output, 1);
					close(fd[0]);
					//printf("executing command %s in child\n", pipe_cmd_arr[j]);
					execute_command_pipe(list, home_dir, cmd_cnt_in_pipe, pipe_cmd_arr[j]);
					exit(2);
				}
				else
				{

					wait(NULL);
					close(fd[1]);
					pipe_input = fd[0];
				}

				continue;
			}

			else if (output_file_append == NULL && output_file_normal != NULL)
			{
				char *output_file_name;
				output_file_name = strtok(output_file_normal + 1, " \t\r\n\v\f");
				int fd_output = open(output_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				//dup2(fd_output, 0);
				char **list;
				cmd_cnt_in_pipe = 0;
				list = extract_command(pipe_cmd_arr[j], &cmd_cnt_in_pipe);

				pipe(fd);
				pid = fork();
				if (pid == 0)
				{
					dup2(pipe_input , 0);
					//if (pipe_cmd_arr[j + 1] != NULL)
					//	dup2(fd[1], 1);
					dup2(fd_output, 1);
					close(fd[0]);
					//printf("executing command %s in child\n", pipe_cmd_arr[j]);
					execute_command_pipe(list, home_dir, cmd_cnt_in_pipe, pipe_cmd_arr[j]);
					exit(2);
				}
				else
				{

					wait(NULL);
					close(fd[1]);
					pipe_input = fd[0];
				}

				continue;
			}

		}

		//all the other cases
		char **list;
		cmd_cnt_in_pipe = 0;
		list = extract_command(pipe_cmd_arr[j], &cmd_cnt_in_pipe);


		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(pipe_input , 0);
			if (pipe_cmd_arr[j + 1] != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			//printf("executing command %s in child\n", pipe_cmd_arr[j]);
			execute_command_pipe(list, home_dir, cmd_cnt_in_pipe, pipe_cmd_arr[j]);
			exit(2);
		}
		else
		{

			wait(NULL);
			close(fd[1]);
			pipe_input = fd[0];
		}

	}

	dup2(std_in_saved, STDIN_FILENO);
	dup2(std_out_saved, STDOUT_FILENO);
	return 1;
}


void execute_command_pipe(char **list, char *home_dir, int cnt, char *cmd)
{
	if (strcmp(list[0], "cd") == 0)
	{
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
	else
		foreground(list);
}
