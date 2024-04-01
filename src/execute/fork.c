#include "minishell.h"

void handle_error(const char *message)
{
    perror(message);
    exit(1);
}

// in - read out - write
int pipe_it(t_data *data)
{
    t_cmd *current = data->commands;

    while (current != NULL)
    {
        pid_t pid = fork();

        if (pid == -1)
            handle_error("fork error");
        else if (pid == 0)
        {
            if (current->pipe_in != -1)
            {
                if (dup2(current->pipe_in, STDIN) == -1)
                    handle_error("dup2 error");
                close(current->pipe_in);
            }

            if (current->pipe_out != -1)
            {
                if (dup2(current->pipe_out, STDOUT) == -1)
                    handle_error("dup2 error");
                close(current->pipe_in);
            }
            exec_cmd(data, current);
            handle_error("exec error");
        }
        else // parent
        {
            if (current->pipe_out != -1)
                close(current->pipe_out);
            if (current->pipe_in != -1)
                close(current->pipe_in);
            current = current->next;
        }
    }

    wait(NULL);
    return 0;
}