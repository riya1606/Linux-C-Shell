#include "headers.h"
char *command_array[1000];
char *temp[1000];
char** extract_command(char *input, int *cnt)
{

	temp[0] = strtok(input, " \t\r\n\v\f"); //separating the commands
	(*cnt) = (*cnt) + 1;
	long long int i = 0, j = 0;
	while (temp[i] != NULL)
	{	//printf("hi\n");
		(*cnt) = (*cnt) + 1;
		i++;
		temp[i] = strtok(NULL, " \t\r\n\v\f");
	}
	int temp_cnt = *cnt;
	(*cnt) = 0;

	for (int i = 0; i < temp_cnt - 1; i++)
	{
		//printf("temp [%d] = %s\n", i, temp[i]);
		//printf("hi 1\n");
		if (strstr(temp[i], "<") != NULL)
		{
			//printf("hi 2\n");
			if (temp[i][0] == '<')
			{
				//printf("hi 3\n");
				if (strlen(temp[i]) == 1)
				{
					//printf("hi 4\n");
					i++;
					continue;
				}
				else
				{
					//printf("hi 5\n");
					continue;
				}
			}
			else
			{
				//printf("hi 6\n");
				command_array[j] = (char*)malloc(200 * sizeof(char));
				strcpy(command_array[j], temp[i]);
				command_array[j][strlen(temp[i]) - 1] = '\0';
				i++;
				j++;
				(*cnt) = (*cnt) + 1;
			}

		}

		else if (strstr(temp[i], ">") != NULL)
		{
			if (temp[i][0] == '>')
			{
				if (strlen(temp[i]) == 1)
				{
					i++;
					continue;
				}

				else if (temp[i][1] == '>')
				{
					if (strlen(temp[i]) == 2)
					{
						i++;
						continue;
					}

					else
						continue;
				}
			}
			else
			{

				command_array[j] = (char*)malloc(200 * sizeof(char));
				strcpy(command_array[j], temp[i]);
				command_array[j][strlen(temp[i]) - 1] = '\0';
				if (command_array[j][strlen(temp[i]) - 2] == '>')
					command_array[j][strlen(temp[i]) - 2] = '\0';
				j++;
				i++;
				(*cnt) = (*cnt) + 1;
			}
		}

		else
		{
			//printf("hi 7\n");
			command_array[j] = (char*)malloc(200 * sizeof(char));
			strcpy(command_array[j], temp[i]);
			j++;
			(*cnt) = (*cnt) + 1;
		}
		//printf("hi 8\n");
	}

	command_array[(*cnt)] = NULL;
	(*cnt) = (*cnt) + 1;
	return command_array;

}