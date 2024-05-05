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
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 2;
	}
}

// rpl_exit_code(int exit_status)
// {
// 	g_signal = exit_status;
// 	data
// }