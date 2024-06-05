#include "minishell.h"

// void sig_handler_f(int sig)
// {
// 	(void)sig;
// 	if (sig == SIGINT)
//     {
// 	 	printf("\n");
//      	rl_on_new_line();
// 	// 	rl_replace_line("", 0);
// 	// 	rl_redisplay();
// 	// 	clear_history();
//         g_signal = 2;
// 	}
// 	// else if (sig == SIGPIPE)
// 	// {
// 	// 	g_signal = 1;
// 	// }
// }

// void handle_ctr_f()
// {
// 	signal(SIGINT, sig_handler_f);
//     //signal(SIGPIPE, sig_handler_f);
// 	//signal(SIGQUIT, sig_handler_f);
// }


// void handle_sigint_f(int sig) {
//     (void)sig;
//     g_signal = 1;
//     //printf("\nYou have pressed CTRL-C\n");
// 	ioctl(0, TIOCSTI, "\n");
// 	//rl_replace_line("", 0);
// }



int pipe_cmds(t_data *data)
{
    t_cmd *current;
    pid_t pid[data->num_of_children];
    int i;

    i = 0;
    current = data->commands;
    //handle_ctr_f();
    while (current != NULL)
    {
        pid[i] = fork();
        if (pid[i] == -1)
            return EXIT_FAILURE;
        else if (pid[i] == 0)
        {
            fd_dup2(current);
            ultimate_fd_close(data);
            exec_cmd(data, current);
            exit(data->exit_code);
        }
        else
            fd_close(current);
        current = current->next;
        i++;
    }
    ultimate_wait(data, pid);
    return EXIT_SUCCESS;
}
