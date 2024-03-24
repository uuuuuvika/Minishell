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
    printf(BLU"Command 0: %s. ",commands[0]);
    printf(BLU "Command 1: %s\n"WHT,commands[1]);
    int read_e = data->commands[0].pipe_out;
    int write_e = data->commands[1].pipe_in;
    // printf("PIPE 1: %d\n", read_e);
    // printf("PIPE 2: %d\n", write_e);

    int pipe[2];
    pipe[PIPE_READ] = read_e;
    pipe[PIPE_WRITE] = write_e;
    printf(BLU "Num of int children passed to struct: %d\n" RESET, data->num_of_children);
    while (i < data->num_of_children)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork error");
            return (1);
        }
        printf("ENTERS LOOP\n");
        if (pid == 0)
        {
            if (data->num_of_children == 1)
            {
                printf(RED"Executing in child\n"RESET);
                exec_cmd(data, commands[i]);
                exit(0);
            }
            if (i == 0 && data->num_of_children > 1)
            {
                printf("Loop1 %s ", commands[i]);
                close(pipe[PIPE_READ]);
                // int dup2(int oldfd, int newfd);
                dup2(pipe[PIPE_WRITE], STDIN);
                close(pipe[PIPE_WRITE]);
                exec_cmd(data, commands[i]);
            }
            if (i == 1 && data->num_of_children > 1)
            {
                printf("Loop2 %s ", commands[i]);
                close(pipe[PIPE_WRITE]);
                // int dup2(int oldfd, int newfd);
                dup2(pipe[PIPE_READ], STDOUT);
                close(pipe[PIPE_READ]);
                 exec_cmd(data, commands[i]);
            }
            printf(BLU "Passing command: %s\n " RESET, commands[i]);
        }
        else
        {
            printf("Parent with pid %d waiting\n",pid);
            wait(NULL);
                close(pipe[PIPE_WRITE]);
                close(pipe[PIPE_READ]);
        }
        i++;
    }
    return 0;
}
