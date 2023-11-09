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
