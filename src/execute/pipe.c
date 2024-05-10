#include "minishell.h"

void handle_error(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int pipe_cmds(t_data *data)
{
    t_cmd *current;
    pid_t pid[data->num_of_children];
    int exit_code;
    //int pid_array[data->num_of_children];

    current = data->commands;
    int i = 0;
    while (current != NULL)
    {
        pid[i] = fork();
        printf("looping through commands\n");
        if (pid[i] == -1)
            return EXIT_FAILURE;

        else if (pid[i] == 0)
        {
            if (current->pipe_in != -1)
            {
                if (dup2(current->pipe_in, STDIN_FILENO) == -1)
                    handle_error("dup2 error pipe_in");
                close(current->pipe_in);
            }
            else if (current->redirect_in != -1)
            {
                if (dup2(current->redirect_in, STDIN_FILENO) == -1)
                    handle_error("dup2 error redirect_in");
                close(current->redirect_in);
            }

            if (current->redirect_out != -1)
            {
                if (dup2(current->redirect_out, STDOUT_FILENO) == -1)
                    handle_error("dup2 error redirect_out");
                close(current->redirect_out);
            }
            else if (current->pipe_out != -1)
            {
                if (dup2(current->pipe_out, STDOUT_FILENO) == -1)
                    handle_error("dup2 error pipe_out");
                close(current->pipe_out);
            }
            printf("executing command: %s\n", current->args[0]);
            exit(exec_cmd(data, current));
        }
        else
        {
            if (current->pipe_out != -1)
            {
                close(current->pipe_out);
                printf("[parent] pipe out: closed file descriptor: %d\n", current->pipe_out);
            }
            if (current->pipe_in != -1)
            {
                close(current->pipe_in);
                printf("[parent] pipe in: closed file descriptor: %d\n", current->pipe_in);
            }
            if (current->redirect_in != -1)
                close(current->redirect_in);
            if (current->redirect_out != -1)
                close(current->redirect_out);
        }
        current = current->next;
        i++;
    }
    i = 0;
    while (i < data->num_of_children)
    {
        printf("pid[%d]: %d\n", i, pid[i]);
        if (waitpid(pid[i], &exit_code, 0) == -1)
        {
            perror("waitpid failed");
            return EXIT_FAILURE;
        }
        if (WIFEXITED(exit_code))
            data->exit_code = WEXITSTATUS(exit_code);
        i++;
    }
    // if (waitpid(pid, &exit_code, 0) == -1)
    // {
    //     perror("waitpid failed");
    //     return EXIT_FAILURE;
    // }
    // if (WIFEXITED(exit_code))
    //     data->exit_code = WEXITSTATUS(exit_code);
    return EXIT_SUCCESS;
}
