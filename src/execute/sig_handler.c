#include "minishell.h"

int g_signal = 0;

void handle_ctrl()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void sig_handler(int sig)
{
	if (sig == SIGINT)
  	{
	//	printf(MAG"handle_ctrl\n"RESET);
		ioctl(0, TIOCSTI, "\n");
		//printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 1);
		//rl_redisplay();
		g_signal = 2;
		//printf(CYN "g_singal %d" RESET,g_signal);
	}
	else if (sig == 13)
	{
		g_signal = 1;
	}
}
