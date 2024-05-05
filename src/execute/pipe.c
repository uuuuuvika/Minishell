#include "minishell.h"

void handle_error(const char *message)
{
    perror(message);
    // exit(0);
}

// in - read - 0 --------------- out - write - 1
// int pipe_cmds(t_data *data)
// {
//     t_cmd *current;
//     pid_t pid;

//     current = data->commands; // cat | cat | ls
//     while (current != NULL)
//     {
//         pid = fork();
//         if (pid == -1)
//             return EXIT_FAILURE;
//         // handle_error("fork error");
//         else if (pid == 0)
//         {
//             if (current->pipe_in != -1)
//             {
//                 if (dup2(current->pipe_in, STDIN) == -1)
//                     handle_error("dup2 error pipe_in");
//                 close(current->pipe_in);
//             }
//             else if (current->redirect_in != -1)
//             {
//                 if (dup2(current->redirect_in, STDIN) == -1)
//                     handle_error("dup2 error redirect_in");
//                 close(current->redirect_in);
//             }

//             if (current->redirect_out != -1)
//             {
//                 if (dup2(current->redirect_out, STDOUT) == -1)
//                     handle_error("dup2 error redirect_out");
//                 close(current->redirect_out);
//             }

//             else if (current->pipe_out != -1)
//             {
//                 if (dup2(current->pipe_out, STDOUT) == -1)
//                     handle_error("dup2 error pipe_out");
//                 close(current->pipe_out);
//             }

//             exec_cmd(data, current);
//             // handle_error("exec_cmd error"); // This is error is printed after executung builtins, there is already an error check when executing execve
//             return EXIT_FAILURE;
//         }
//         else
//         {
//             //wait(NULL); //
//             if (current->pipe_out != -1)
//                 close(current->pipe_out);
//             if (current->pipe_in != -1)
//                 close(current->pipe_in);

//             if (current->redirect_in != -1)
//                 close(current->redirect_in);
//             if (current->redirect_out != -1)
//                 close(current->redirect_out);

//             current = current->next;
//         }
//     }
//     waitpid(pid, &data->exit_code, 0);
//     return EXIT_SUCCESS;
// }

#include <sys/wait.h> // for waitpid

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
            int j = 0;
            j = exec_cmd(data, current);
            handle_error("exec_cmd error"); // This is error is printed after executung builtins, there is already an error check when executing execve
            exit(j);
        }
        else
        {
            if (current->pipe_out != -1)
                close(current->pipe_out);
            if (current->pipe_in != -1)
                close(current->pipe_in);
            if (current->redirect_in != -1)
                close(current->redirect_in);
            if (current->redirect_out != -1)
                close(current->redirect_out);
        }
        current = current->next;
    }

    // waitpid(pid, &exit_code, 0);
    // data->exit_code = exit_code;
   
    if (waitpid(pid, &exit_code, 0) == -1)
    {
        perror("waitpid failed");
        return EXIT_FAILURE;
    }
    printf("exit code in pipe_cmds is %d\n", WEXITSTATUS(exit_code));

    if (WIFEXITED(exit_code))
    {
        //const int es = WEXITSTATUS(exit_code);
        data->exit_code = exit_code;
        printf("exit status was %d\n", exit_code);
    }

    return EXIT_SUCCESS;
}
