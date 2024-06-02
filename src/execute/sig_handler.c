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
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 2;
	}
	else if (sig == 13)
	{
		g_signal = 1;
	}
}



// int g_signal = 0;

// void sig_handler(int sig) {
//     if (sig == SIGINT) {
//         printf("\n");
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//         g_signal = 2;
//         rl_done = 1;
//     } else if (sig == 13) {
//         g_signal = 1;
//     }
// }

// void handle_ctrl() {
//     struct sigaction sa;
//     sa.sa_handler = sig_handler; // Correct assignment of the signal handler
//     sa.sa_flags = 0;
//     sigemptyset(&sa.sa_mask);

//     sigaction(SIGINT, &sa, NULL); // Correct use of sigaction
//     signal(SIGQUIT, SIG_IGN);
// }