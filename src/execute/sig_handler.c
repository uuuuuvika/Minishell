#include "minishell.h"

int g_signal = 0;

// void handle_ctrl()
// {
// 	signal(SIGINT, sig_handler);
// 	signal(SIGQUIT, sig_handler);
// }

void sig_handler(int sig)
{
	(void)sig;
	ioctl(0, TIOCSTI, "\n");
	g_signal = 2; // so far it is not used 
}

// void sig_handler(int sig)
// {
// 	(void)sig;
// 	// if (sig == SIGPIPE)
// 	// {
// 	// 	printf("\n");
// 	// 	rl_on_new_line();
// 	// 	rl_replace_line("", 0);
// 	// 	rl_redisplay();
// 	// 	clear_history();
// 	// 	// g_signal = 2;
// 	// }
// 	// else if (sig == SIGPIPE)
// 	// {
// 	// 	g_signal = 1;
// 	// }
// }
