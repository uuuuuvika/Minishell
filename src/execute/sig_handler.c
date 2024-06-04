#include "minishell.h"

int g_signal = 0;

void handle_ctrl()
{
	//signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}


void handle_sigint(int sig) {
    (void)sig;
    g_signal = 1;
    //printf("\nYou have pressed CTRL-C\n");
	ioctl(0, TIOCSTI, "\n");
	//rl_replace_line("", 0);
}

void sig_handler(int sig)
{
	(void)sig;
	// if (sig == SIGPIPE)
	// {
	// 	printf("\n");
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// 	clear_history();
	// 	// g_signal = 2;
	// }
	// else if (sig == SIGPIPE)
	// {
	// 	g_signal = 1;
	// }
}
