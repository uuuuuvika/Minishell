#include "minishell.h"

int pipe_it(t_data *data)
{
    pid_t pid;
    int i = 0;

    char **commands;
    commands = malloc(5 * sizeof(char *));
    commands[0] = *data->commands[0].args;
    commands[1] = *data->commands[1].args;
    // commands[2] = *data->commands[2].args;
    printf("Command 0: " BLU " %s " RESET, commands[0]);
    printf("Command 1: " BLU "%s\n" RESET, commands[1]);
    int read_e = data->commands[0].pipe_out;
    int write_e = data->commands[1].pipe_in;
    // printf("PIPE 1: %d\n", read_e);
    // printf("PIPE 2: %d\n", write_e);

    int pipe[2];
    pipe[PIPE_READ] = read_e;
    pipe[PIPE_WRITE] = write_e;
    printf("Num of int children passed to struct: " BLU "%d\n" RESET, data->num_of_children);
    while (i < data->num_of_children)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork error");
            exit (1);
        }
        printf("ENTERS LOOP\n");
        if (pid == 0)
        {
            if (data->num_of_children == 1)
            {
                printf(BLU "Executing simple cmd in child\n" RESET);
                exec_cmd(data, commands[i]);
                exit(0);
            }
            if (i == 0 && data->num_of_children > 1)
            {
                printf("LOOP 1" BLU " %s " RESET, commands[i]);
                close(pipe[PIPE_READ]);
                // PROTOTYPE: int dup2(int oldfd, int newfd);
                dup2(pipe[PIPE_WRITE], STDIN);
                close(pipe[PIPE_WRITE]);
                exec_cmd(data, commands[i]);
            }
            if (i == 1 && data->num_of_children > 1)
            {
                printf("LOOP 2 " BLU "%s " RESET, commands[i]);
                close(pipe[PIPE_WRITE]);
                // PROTOTYPE: int dup2(int oldfd, int newfd);
                dup2(pipe[PIPE_READ], STDOUT);
                close(pipe[PIPE_READ]);
                exec_cmd(data, commands[i]);
            }
            printf("Passing command: " BLU " %s\n " RESET, commands[i]);
        }
        else
        {
            printf("Parent with pid %d waiting\n",pid);
            wait(NULL);
            if (data->num_of_children > 1)
            {
                close(pipe[PIPE_WRITE]);
                close(pipe[PIPE_READ]);
            } 
        }
        i++;
    }
    return 0;
}
