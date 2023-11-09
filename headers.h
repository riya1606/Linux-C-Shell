#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "prompt.h"
#include "ec.h"
#include "echo.h"
#include "background.h"
#include "pwd.h"
#include "dirent.h"
#include "ls.h"
#include "pinfo.h"
#include "foreground.h"
#include "rfc.h"
#include "jobs.h"
#include "history.h"
#include "ec_semi.h"
#include "execute_command.h"
#include "piping.h"
#include "cd.h"
#include "overkill.h"
#include "setenv_unsetenv.h"
#include <sys/stat.h>

struct jobs
{
	char name[50];
	pid_t pid;
};
struct jobs job_arr[1000];
int job_cnt;

int SHELLID;
int CHILDPID;


#endif
