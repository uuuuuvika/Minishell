#include "minishell.h"

int parse(char *input, t_data *data)
{
    char *line_copy;
    char **future_children;
    char str[20];

    if (input == NULL)
    {
        printf("Error! Input is NULL.\n");
        return -1;
    }

    line_copy = strdup(input);

    if (line_copy == NULL)
    {
        printf("Error!\n");
        return -1;
    }

    data->sub = malloc(10 * sizeof(char **));
    data->commands = malloc(10 * sizeof(t_command));
    // printf("LINE COPY ----> %s\n", line_copy);
    int index = 0;
    int s_index = 0;
    while (line_copy[index])
    {
        if (line_copy[index] == '"')
        {
            int str_index = 0;
            while (line_copy[++index] != '"')
            {
                str[str_index++] = line_copy[index];
                line_copy[index] = '*';
            }
            str[str_index] = '\0';
            data->sub[s_index++] = strdup(str);
        }
        index++;
    }
    data->sub[s_index] = NULL;
    // printf("LINE COPY ----> %s\n", line_copy);

    future_children = ft_split(line_copy, '|');

    index = 0;
    while (future_children[index])
    {
        data->num_of_children++;
        data->commands[index].args = ft_split(future_children[index], ' ');
        index++;
    }

    index = 0;
    while (index < data->num_of_children - 1)
    {
        if (pipe(data->pipes[index]) == -1)
        {
            perror("pipe error!!\n");
            return (-1);
        }
        index++;
    }

    index = 0;
    while (future_children[index])
    {
        data->commands[index].pipe_in = -1;
        data->commands[index].pipe_out = -1;

        if (index > 0)
        {
            data->commands[index - 1].pipe_out = data->pipes[index - 1][PIPE_READ];
            data->commands[index].pipe_in = data->pipes[index - 1][PIPE_WRITE];
        }
        index++;
    }

    index = 0;
    while (index < data->num_of_children)
    {
        int i = 0;
        while(data->commands[index].args[i])
        {
            data->commands[index].num_args++;

            if(strcmp(data->commands[index].args[i], ">") == 0)
            {
                // --- WIP
                // data->commands[index].redirect_out = fopen(data->commands[index].args[i + 1]);
                // data->commands[index].args[i] = NULL;
                // data->commands[index].args[i + 1] = NULL;
                // printf("Redirect out: %d\n", data->commands[index].redirect_out);
                // close(data->commands[index].redirect_out);
                printf("Redirect out!!!\n");
            }
            i++;

        }
        index++;
    }
    // printf("NUM OF ARGS 1st cmd: %d\n", data->commands[0].num_args);
    // printf("NUM OF ARGS 2nd cmd: %d\n", data->commands[1].num_args);


    index = 0;
    while (index < data->num_of_children)
    {
        printf("PIPE IN [%d]: %d\n", index, data->commands[index].pipe_in);
        printf("PIPE OUT [%d]: %d\n", index, data->commands[index].pipe_out);

        index++;
    }

    return (0);
}

int pipe_it(t_data *data)
{
    pid_t pid;
    int i = 0;

    char **commands;
    commands = malloc(5 * sizeof(char *));
    commands[0] = *data->commands[0].args;
    commands[1] = *data->commands[1].args;
    // commands[2] = data->commands[2].args;

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
        if (pid == 0)
        {
            if (i == 0)
            {
                printf("Loop1 %s ", commands[i]);
                close(pipe[PIPE_READ]);
                dup2(pipe[PIPE_WRITE], STDOUT);
                close(pipe[PIPE_WRITE]);
            }
            if (i == 1)
            {
                printf("Loop2 %s ", commands[i]);
                close(pipe[PIPE_WRITE]);
                dup2(pipe[PIPE_READ], STDIN);
                close(pipe[PIPE_READ]);
            }
            printf(BLU "Passing command: %s\n " RESET, commands[i]);
            // PROTOTYPE: void exec_cmd(t_data *data, char *const cmd[])
            //   exec_cmd(data, &commands[i]);
            //  if (execve(paths[i], &commands[i], NULL) == -1)
            //  {
            //      perror(RED"execve"RESET);
            //      exit(1);
            //  }
        }
        else
        {
            printf("%d\n", pid);
            printf("Parent waiting\n");
            wait(NULL);
            close(pipe[PIPE_READ]);
            close(pipe[PIPE_WRITE]);
        }
        i++;
    }
    return 0;
}
