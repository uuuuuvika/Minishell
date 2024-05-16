#include "minishell.h"

int pipe_cmds(t_data *data)
{
    t_cmd *current;
    pid_t pid[data->num_of_children];
    int i;

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
