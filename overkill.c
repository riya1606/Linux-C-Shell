#include "headers.h"

void overkill()
{
	for (int i = 0; i <= job_cnt; i++)
		kill(job_arr[i].pid, 9);

	return;
}