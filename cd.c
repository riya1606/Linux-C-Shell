#include "headers.h"

char *cd_list[1000];
int cd_change = 1;

int cd_call(char** list, char *input, char* home_dir)
{
	//printf("hello from cd\n");
	cd_list[0] = (char*)malloc(200 * sizeof(char));
	strcpy(cd_list[0], home_dir);
	cd_list[0][strlen(home_dir)] = '\0';
	//printf("cd_list[0] = %s\n", cd_list[0]);
	//printf("cd_change = %d\n", cd_change );

	if ((list[1] == NULL) || (strcmp(list[1], "~") == 0))
	{
		//printf("(list[1] == NULL) || (strcmp(list[1], ~) == 0)\n");
		if (chdir(home_dir) != 0)
			return -1;


		//char cwd[1024];
		//getcwd(cwd, 1024);
		//rintf("%s\n", cwd);

		cd_change++;
		char cwd[1024];
		getcwd(cwd, 1024);
		cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
		strcpy(cd_list[cd_change], cwd);
		cd_list[cd_change][strlen(cwd)] = '\0';
		//if this condition is entered, we have to return 0. because if it goes foward, in case of cd
		//list[1]==NULL, and we are accessing it right after this. and so seg fault. hence returning 0.
		return 0;
	}



	if ((strcmp(list[1], "-") == 0))
	{
		//printf("cd_change = %d\n", cd_change);
		if (cd_change == 1)
		{
			//printf("cd_change = %d\n", cd_change);
			char cwd[1024];
			getcwd(cwd, 1024);
			printf("%s\n", cwd);
		}
		else
		{
			//printf("%s\n", cd_list[cd_change - 1]);
			char *copy1_of_last_dir;
			copy1_of_last_dir = (char*)malloc(200 * sizeof(char));
			strcpy(copy1_of_last_dir, cd_list[cd_change - 1]);
			//printf("last dir = %s\n", copy1_of_last_dir );
			char *temp_dir_name;
			temp_dir_name = (char*)malloc(200 * sizeof(char));

			if (strstr(copy1_of_last_dir, home_dir) != NULL)
			{

				temp_dir_name[0] = '~';
				int k = 1;
				for (int j = strlen(home_dir); j < strlen(cd_list[cd_change - 1]); j++)
				{
					temp_dir_name[k] = cd_list[cd_change - 1][j];
					k++;

				}
				temp_dir_name[k] = '\0';
				printf("%s\n", temp_dir_name);
				chdir(cd_list[cd_change - 1]);
			}
			else
			{
				strcpy(temp_dir_name, cd_list[cd_change - 1]);
				temp_dir_name[strlen(cd_list[cd_change - 1])] = '\0';
				printf("%s\n", temp_dir_name);
				chdir(cd_list[cd_change - 1]);

			}

			cd_change++;
			char cwd[1024];
			getcwd(cwd, 1024);
			cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
			strcpy(cd_list[cd_change], cwd);
			cd_list[cd_change][strlen(cwd)] = '\0';


			/*
			if (cd_list[cd_change - 1][0] == '~')
			{
				//making a buf array with '~' sign at first place
				int i = 1, j = 0;
				char buf[1024];
				while (cd_list[cd_change - 1][i] != '\0')
				{
					buf[j] = cd_list[cd_change - 1][i];
					j++;
					i++;
				}
				buf[j] = '\0';

				//strcat to create path
				char dirname[1024] = "";
				//cat path of home_dir
				strcat(dirname, home_dir);
				//cat buf after home_dir
				strcat(dirname, buf);
				printf("%s\n", dirname);
				if (chdir(dirname) != 0)
					return -1;
				cd_change++;
				cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
				strcpy(cd_list[cd_change], cd_list[cd_change - 2]);
				cd_list[cd_change][strlen(cd_list[cd_change - 2])] = '\0';
			}
			else
			{
				//printf("%s", cd_list[cd_change])
				if (chdir(cd_list[cd_change - 1]) != 0)
					return -1;
				cd_change++;
				cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
				strcpy(cd_list[cd_change], cd_list[cd_change - 2]);
				cd_list[cd_change][strlen(cd_list[cd_change - 2])] = '\0';
				//printf("%s\n", cd_list[cd_change]);
			}
			*/

		}
		//if this condition is entered, we have to return 0. because if it goes foward, in case of cd
		//list[1]==NULL, and we are accessing it right after this. and so seg fault. hence returning 0.
		return 0;
	}

	//making a copy of input token[1];
	char path[1024];
	char ch = list[1][0];
	strcpy(path, list[1]);
	//printf("path[0] : %c\n", path[0] );

	if (path[0] == '~')
	{
		//printf("list[1][0] = ~\n");
		//making a buf array with '~' sign at first place
		int i = 1, j = 0;
		char buf[1024];
		while (path[i] != '\0')
		{
			buf[j] = path[i];
			j++;
			i++;
		}
		buf[j] = '\0';

		//strcat to create path
		char dirname[1024] = "";
		//cat path of home_dir
		strcat(dirname, home_dir);
		//cat buf after home_dir
		strcat(dirname, buf);
		//printf("%s\n", dirname);
		if (chdir(dirname) != 0)
			return -1;

		cd_change++;
		char cwd[1024];
		getcwd(cwd, 1024);
		cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
		strcpy(cd_list[cd_change], cwd);
		cd_list[cd_change][strlen(cwd)] = '\0';
	}

	else if (strcmp(list[1], "/") == 0)
	{
		//printf("list[1] = /\n");

		if (chdir("/") != 0)
			return -1;
		cd_change++;
		char cwd[1024];
		getcwd(cwd, 1024);
		cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
		strcpy(cd_list[cd_change], cwd);
		cd_list[cd_change][strlen(cwd)] = '\0';
	}

	else
	{

		//printf("else case 145\n");
		if (chdir(list[1]) != 0)
			return -1;

		//printf("chdir done properly\n");
		cd_change++;
		char cwd[1024];
		getcwd(cwd, 1024);
		cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
		strcpy(cd_list[cd_change], cwd);
		cd_list[cd_change][strlen(cwd)] = '\0';
	}

	return 0;
}