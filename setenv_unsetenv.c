#include "headers.h"

void setenv_call(char **list, int cnt)
{
    if (cnt != 3)
        printf("Error: Incorrect number of arguments\n");
    else
    {
        int ret = setenv(list[1], list[2], 1);
        if (ret < 0)
            perror("Error setting env:");
    }
}

void unsetenv_call(char **list, int cnt)
{
    if (cnt == 1)
        printf("Error: Check command. Variable name not provided\n");
    else if (cnt != 2)
        perror("Error:");
    else
    {
        int ret = unsetenv(list[1]);
        if (ret < 0)
            perror("Error:");
    }
}