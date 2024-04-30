#include "minishell.h"

void handle_error(const char *message)
{
    perror(message);
    exit(0);
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
                    handle_error("dup2 error pipe_in");
                close(current->pipe_in);
            } 
            else if (current->redirect_in != -1)
            {
                if (dup2(current->redirect_in, STDIN) == -1)
                    handle_error("dup2 error redirect_in");
                close(current->redirect_in);
            }

            if (current->redirect_out != -1)
            {
                if (dup2(current->redirect_out, STDOUT) == -1)
                    handle_error("dup2 error redirect_out");
                close(current->redirect_out);
            }

            else if (current->pipe_out != -1)
            {
                if (dup2(current->pipe_out, STDOUT) == -1)
                    handle_error("dup2 error pipe_out");
                close(current->pipe_out);
            }
           
            exec_cmd(data, current);
            handle_error("exec_cmd error");// This is error is printed after executung builtins, there is already an error check when executing execve
        }
        else
        {
            wait(NULL);
            if (current->pipe_out != -1)
                close(current->pipe_out);
            if (current->pipe_in != -1)
                close(current->pipe_in);
            if(current->redirect_in != -1)
                close(current->redirect_in);
            if(current->redirect_out != -1)
                close(current->redirect_out);
            current = current->next;
        }
    }
    wait(NULL);
    return 0;
}

// int redirect_in(t_data *data, t_cmd *current)
// {
//     int fd;

//     fd = open(current->args[1], O_RDWR | O_CREAT);
//     if (fd == -1)
//         handle_error("open error");
//     if (dup2(fd, STDIN) == -1)
//         handle_error("dup2 error redirect_in");
//     close(fd);
//     return 0;
// }