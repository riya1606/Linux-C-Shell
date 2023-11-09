#include "headers.h"
#include "prompt.h"
#include "ec.h"
#include "cd.h"
int cnt = 0;
int cnt_semi = 0;

void CTRL_C(int SIG);
int main ()
{

	CHILDPID = -1;
	SHELLID = 0;
	//piping reset input-output
	int std_in_saved = dup(0);
	int std_out_saved = dup(1);
	dup2(std_in_saved, STDIN_FILENO);
	dup2(std_out_saved, STDOUT_FILENO);
	//storing home_dir path in p
	char* home_dir = get_homedir();


	signal(SIGINT, CTRL_C);
	SHELLID = getpid();

	while (1)
	{
		cnt_semi = 0;
		char* input;
		size_t size = 0;
		prompt();

		//Taking input after every prompt
		getline(&input, &size, stdin);
		//printf("%lu\n", strlen(input) );
		//Exracting the input command
		//printf("came back to main\n");
		update_hist(input, strlen(input));
		//printf("input %s\n", input );
		if (strlen(input) < 1)
			continue;
		if (input[0] == '\n')
			continue;
		if (strlen(input) == 1 && input[0] == ' ')
			continue;

		for (int i = 0; i < strlen(input); i++)
		{
			if (input[i] == ';')
				cnt_semi++;
		}

		if (cnt_semi != 0)
		{
			char **cmd = extract_semicolon(input, &cnt_semi);
			//printf("cnt_semi = %d\n", cnt_semi);
			for (int j = 0; cmd[j] != NULL; j++)
			{
				//printf("cnt_semi = %d\n", cnt_semi);
				//printf("hi1\n");
				cnt = 0;
				//piping check
				int ret = piping(cmd[j], home_dir);
				if (ret == 1)
					continue;

				//printf("doing redirection flag check 61\n");
				//if no piping then execute command in main.
				//redirection check in case of semicolon command
				red_flag_check(cmd[j]);
				char **list;
				//printf("helo helo helo\n");
				list = extract_command(cmd[j], &cnt);
				if (cnt == 0)
				{
					//printf("cnt==0 so continuing\n");
					continue;
				}
				execute_command(list, home_dir, cnt, cmd[j]);

				//piping dup reset input-output
				dup2(std_in_saved, STDIN_FILENO);
				dup2(std_out_saved, STDOUT_FILENO);

			}

		}
		else
		{

			char input_copy[1024];
			strcpy(input_copy, input);
			char **list;
			cnt = 0;
			list = extract_command(input_copy, &cnt);
			//printf("hi1\n");
			//printf("cnt  = %d line 92 main\n", cnt);
			if (cnt == 1)
				continue;
			//piping check in case of no semicolon
			int ret = piping(input, home_dir);
			if (ret == 1)
				continue;

			//printf("doing redirection flag check 78\n");
			//if no piping then execute command in main.
			//redirection check in case of no semicolon
			red_flag_check(input);
			//printf("doing redirection flag check 78\n");
			//char **list;

			//printf("helo helo helo\n");
			//list = extract_command(input, &cnt);

			if (cnt == 1)
				continue;
			//printf("hi from 111\n");
			execute_command( list, home_dir, cnt, input);

			//piping dup reset input output
			dup2(std_in_saved, STDIN_FILENO);
			dup2(std_out_saved, STDOUT_FILENO);
		}


	}

}


void CTRL_C(int SIG)
{
	int pid = getpid();
	if (pid != SHELLID)
	{
		return;
	}
	if (CHILDPID != -1)
	{
		kill(CHILDPID, SIGINT);
		signal(SIGINT, CTRL_C);
	}
}

