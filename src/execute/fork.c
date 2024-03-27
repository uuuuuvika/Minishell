#include "minishell.h"

int pipe_it(t_data *data)
{
    pid_t pid;
    int i = 0;

    t_cmd **commands;
    commands = malloc(5 * sizeof(t_cmd *));
    commands[0] = data->commands;
    commands[1] = data->commands->next;
    // commands[2] = *data->commands[2].args;
    // printf("Command 0: " BLU " %s " RESET, commands[0]);
    // printf("Command 1: " BLU "%s\n" RESET, commands[1]);
    int read_e = data->commands[0].pipe_out;
    int write_e = data->commands[1].pipe_in;
    printf("PIPE 1: %d\n", read_e);
    printf("PIPE 2: %d\n", write_e);

    // int pipe[2];
    // pipe[PIPE_READ] = read_e;
    // pipe[PIPE_WRITE] = write_e;
    printf("Num of children in struct: " BLU "%d\n" RESET, data->num_of_children);
    while (i < data->num_of_children)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork error");
            exit (1);
        }
        if (pid == 0)
        {   
            printf("ENTERS LOOP %d\n", i);
            if (i == 0 && data->num_of_children > 1)
            {
           //     printf("LOOP 1" BLU " %s \n" RESET, commands[i]);
                close(read_e);
                // // PROTOTYPE: int dup2(int newfd, int oldfd);
                dup2(write_e, STDOUT);
                close(write_e);
                exec_cmd(data, commands[0]);
            }
            else if (i == 1 && data->num_of_children > 1)
            {
             //   printf("LOOP 2 %s\n " RESET , commands[i]);
                close(write_e);
                // // PROTOTYPE: int dup2(int newfd, int oldfd);
                dup2(read_e, STDIN);
                close(read_e);
                exec_cmd(data, commands[1]);
            }
        }
        else
        {
            printf(YEL "Child PID " RESET "%d\n", pid);
            printf(YEL "Parent PID %d " RESET "waiting...\n", getpid());
            close(write_e);
        }
        i++;
    }
    wait(NULL);
    close (write_e);
    close (read_e);
    return 0;
}