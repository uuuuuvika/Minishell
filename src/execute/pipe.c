#include "minishell.h"

void sig_handler_fork(int sig)
{
	if (sig == SIGINT)
  	{
		printf("\n");
		g_signal = 0; // need to reset g_signal, otherwise it will be 2 in the next iteration and the program will exit in heredoc
		// printf(MAG"handle_ctrl_fork\n"RESET);
		// printf(CYN "g_singal %d" RESET,g_signal);
	}
}

void handle_ctrl_fork(t_data *data)
{
	if(signal(SIGINT, sig_handler_fork))
		data->exit_code = 130;// !important
	signal(SIGQUIT, SIG_IGN);
}

int pipe_cmds(t_data *data)
{
    t_cmd *current;
    pid_t pid[data->num_of_children];
    int i;

    i = 0;
    current = data->commands;
    while (current != NULL)
    {
		//handle_ctrl_fork(data); // set signal handler for fork
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
	handle_ctrl(); // reset signal handler
    return EXIT_SUCCESS;
}
