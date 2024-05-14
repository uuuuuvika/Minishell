#include "minishell.h"

// void ffd_close(t_cmd *current, t_data *data)
// {
//     t_cmd *temp = data->commands;
//     while (temp->args[0] != current->args[0])
//     {
//         if (temp->pipe_in != -1)
//             close(temp->pipe_in);
//         if (temp->pipe_out != -1)
//             close(temp->pipe_out);
//         if (temp->redirect_in != -1)
//             close(temp->redirect_in);
//         if (temp->redirect_out != -1)
//             close(temp->redirect_out);
//         temp = temp->next;
//     }
// }


int pipe_cmds(t_data *data)
{
    t_cmd *current;
    pid_t pid[data->num_of_children];
    int i;

    i = 0;
    current = data->commands;
    t_cmd *prev = NULL;
    while (current != NULL)
    {
        pid[i] = fork();
        if (pid[i] == -1)
            return EXIT_FAILURE;
        else if (pid[i] == 0)
        {
            handle_dup2(current);
            ultimate_fd_close(data);
            return (exec_cmd(data, current));
        }
        else {
            //ffd_close(current, data);
            fd_close(current);
        }
        prev = current;
        current = current->next;
        i++;
    }
    ultimate_wait(data, pid);
    return EXIT_SUCCESS;
}
