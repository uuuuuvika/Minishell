#include "minishell.h"

void handle_error(const char *message)
{
    perror(message);
    // exit(0);
}

int pipe_cmds(t_data *data)
{
    t_cmd *current;
    pid_t pid;
    int exit_code;

    current = data->commands;
    while (current != NULL)
    {
        pid = fork();
        if (pid == -1)
            return EXIT_FAILURE;
        else if (pid == 0)
        {
            if (current->pipe_in != -1)
            {
                // close(current->pipe_out);
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

            exit(exec_cmd(data, current));
        }
        else
        {
            // if (waitpid(pid, &exit_code, 0) == -1)
            // {
            //     perror("waitpid failed");
            //     data->exit_code = 1;
            //     return EXIT_FAILURE;
            // }
            // if (WIFEXITED(exit_code))
            // {
            //     data->exit_code = WEXITSTATUS(exit_code);
            // }
            do
            {
                pid_t w = waitpid(pid, &exit_code, WUNTRACED | WCONTINUED);
                if (w == -1)
                {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }

                if (WIFEXITED(exit_code))
                {
                    printf("exited, status=%d\n", WEXITSTATUS(exit_code));
                }
                else if (WIFSIGNALED(exit_code))
                {
                    printf("killed by signal %d\n", WTERMSIG(exit_code));
                }
                else if (WIFSTOPPED(exit_code))
                {
                    printf("stopped by signal %d\n", WSTOPSIG(exit_code));
                }
                else if (WIFCONTINUED(exit_code))
                {
                    printf("continued\n");
                }
            } while (!WIFEXITED(exit_code) && !WIFSIGNALED(exit_code));
            //exit(EXIT_SUCCESS);
            // if (current->pipe_out != -1)
            //     close(current->pipe_out);
            // if (current->pipe_in != -1)
            //     close(current->pipe_in);
            // if (current->redirect_in != -1)
            //     close(current->redirect_in);
            // if (current->redirect_out != -1)
            //     close(current->redirect_out);
        }
        current = current->next;
    }

    // if (waitpid(pid, &exit_code, 0) == -1)
    // {
    //     perror("waitpid failed");
    //     data->exit_code = 1;
    //     return EXIT_FAILURE;
    // }

    // if (WIFEXITED(exit_code))
    // {
    //     data->exit_code = WEXITSTATUS(exit_code);
    // }
    return EXIT_SUCCESS;
}
