#include "minishell.h"

void handle_error(const char *message)
{
    perror(message);
    exit(1);
}

// in - read - 0 --------------- out - write - 1
int pipe_cmds(t_data *data)
{
    t_cmd *current;
    pid_t pid;

    current = data->commands;
    while (current != NULL)
    {
        pid = fork();
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
                close(current->pipe_out);
            }
            exec_cmd(data, current);
            handle_error("exec_cmd error");
        }
        else
        {
            wait(NULL);
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