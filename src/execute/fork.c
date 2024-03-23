#include "minishell.h"

int pipe_it(t_data *data)
{
    pid_t pid;
    int i = 0;

    char **commands;
    commands = malloc(5 * sizeof(char *));
    commands[0] = *data->commands[0].args;
    //commands[1] = *data->commands[1].args;
    // commands[2] = *data->commands[2].args;
    printf(RED"????\n"RESET);
    printf("%s ",commands[0]);
   // printf("%s ",commands[1]);
 //   printf("%s\n",commands[0]);
    int read_e = data->commands[0].pipe_out;
    int write_e = data->commands[1].pipe_in;
    // printf("PIPE 1: %d\n", read_e);
    // printf("PIPE 2: %d\n", write_e);

    int pipe[2];
    pipe[PIPE_READ] = read_e;
    pipe[PIPE_WRITE] = write_e;
    printf(BLU "Num of int children passed to struct: %d\n " RESET, data->num_of_children);
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
                exec_cmd(data, data->commands);
                exit(0);
            }
            if (i == 0 && data->num_of_children > 1)
            {
                printf("Loop1 %s ", commands[i]);
                close(pipe[PIPE_READ]);
                dup2(pipe[PIPE_WRITE], STDOUT);
                close(pipe[PIPE_WRITE]);
            }
            if (i == 1 && data->num_of_children > 1)
            {
                printf("Loop2 %s ", commands[i]);
                close(pipe[PIPE_WRITE]);
                dup2(pipe[PIPE_READ], STDIN);
                close(pipe[PIPE_READ]);
            }
            printf(BLU "Passing command: %s\n " RESET, commands[i]);
            // PROTOTYPE: void exec_cmd(t_data *data, char *const cmd[])
            exec_cmd(data, data->commands);
            //  if (execve(paths[i], &commands[i], NULL) == -1)
            //  {
            //      perror(RED"execve"RESET);
            //      exit(1);
            //  }
        }
        else
        {
            printf("Parent with pid %d waiting\n",pid);
            wait(NULL);
            if (data->num_of_children > 1) 
            {
                close(pipe[PIPE_READ]);
                close(pipe[PIPE_WRITE]);
            }
        }
        i++;
    }
    return 0;
}
