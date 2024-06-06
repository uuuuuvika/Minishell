#include "minishell.h"


void sig_handler_fork(int sig)
{
	if (sig == SIGINT)
  	{
	//	printf(MAG"handle_ctrl_fork\n"RESET);
		printf("\n");
		g_signal = 2;
		//printf(CYN "g_singal %d" RESET,g_signal);
	}
	else if (sig == 13)
	{
		g_signal = 1;
	}
}

void handle_ctrl_fork()
{
	signal(SIGINT, sig_handler_fork);
	signal(SIGQUIT, SIG_IGN);
}

int pipe_cmds(t_data *data)
{
    t_cmd *current;
    pid_t pid[data->num_of_children];
    int i;
	handle_ctrl_fork();////// added here
    i = 0;
    current = data->commands;
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
