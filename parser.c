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

    for (int i = 0; i < data->num_of_children - 1; i++)
    {
        if (pipe(data->pipes[i]) == -1)
        {
            perror("pipe got fucked up\n");
            return -1;
        }
    }

    index = 0;
    while (future_children[index])
    {
        data->commands[index].pipe_in = -1;
        data->commands[index].pipe_out = -1;

        if (index > 0)
        {
            // int pipes[2];
            // pipe(pipes);

            data->commands[index - 1].pipe_out = data->pipes[index - 1][0];
            data->commands[index].pipe_in = data->pipes[index - 1][1];
            // data->commands[index - 1].pipe_out = pipes[0];
            // data->commands[index].pipe_in = pipes[1];
        }

        index++;
    }

    // printf("CHILDREN: %d\n", data->num_of_children);

    int i = 0;
    while (i < data->num_of_children)
    {
        printf("PIPE IN [%d]: %d\n", i, data->commands[i].pipe_in);
        printf("PIPE OUT [%d]: %d\n", i, data->commands[i].pipe_out);

        i++;
    }

    return (0);
}

int pipe_it(t_data *data)
{
    pid_t pid;
    int i = 0;

    char *path_1 = ft_strjoin("/bin/", data->commands[0].args[0]);
    char *path_2 = ft_strjoin("/bin/", data->commands[1].args[0]);
   // char *path_3 = ft_strjoin("/bin/", data->commands[2].args[0]);
    char *paths[] = {path_1, path_2};

    // char *cmd_1[5] = data->commands[0].args;
    // char *cmd_2[5] = data->commands[1].args;

    char ***commands;
    commands = malloc(5 * sizeof(char **));
    commands[0] = data->commands[0].args;
    commands[1] = data->commands[1].args;
    //commands[2] = data->commands[2].args;

    int read_e = data->commands[0].pipe_out;
    int write_e = data->commands[1].pipe_in;

    // int read_e_2 = data->commands[1].pipe_out;
    // int write_e_2 = data->commands[2].pipe_in;

    // printf("PIPE 1: %d\n", read_e);
    // printf("PIPE 2: %d\n", write_e);

    int pipe[2];
    pipe[0] = read_e;
    pipe[1] = write_e;

    // int pipe_2[2];
    // pipe_2[0] = read_e_2;
    // pipe_2[1] = write_e_2;

    while (i < 2)
    {
        pid = fork();

        if (pid == -1)
        {
            perror("fork error");
            return (1);
        }
        if (pid == 0)
        {
            //fork();
            if (i == 0)
            {
                close(pipe[0]);
                dup2(pipe[1], 1);
                close(pipe[1]);
            }
            if (i == 1)
            {
                close(pipe[1]);
                dup2(pipe[0], 0);
                close(pipe[0]);
            }
            // if (i == 2)
            // {
            //     close(pipe_2[0]);
            //     dup2(pipe_2[1], 1);
            //     close(pipe_2[1]);
            // }
            // if (i == 2)
            // {
            //     close(pipe_2[0]);
            //     dup2(pipe_2[1], 1);
            //     close(pipe_2[1]);
            // }

            if (execve(paths[i], commands[i], NULL) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
        i++;
    }
    wait(NULL);

    close(pipe[0]);
    close(pipe[1]);
    return 0;
}
