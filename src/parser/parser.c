#include "minishell.h"

int parse(char *input, t_data *data)
{
    char *line_copy;
    char **future_children;

    check_NULL(input);
    line_copy = strdup(input);
    check_NULL(line_copy);
    //substitute double quotes
    sub_quot(line_copy, data);

    future_children = ft_split(line_copy, '|');
    free(line_copy);

    int index = 0;
    t_cmd *head = NULL;
    t_cmd *current = NULL;
    while (future_children[index])
    {
        t_cmd *newNode = (t_cmd *)malloc(sizeof(t_cmd));
        newNode->args = ft_split(future_children[index], ' ');
        newNode->num_args = 0;
        newNode->pipe_in = -1;
        newNode->pipe_out = -1;
        newNode->redirect_in = -1;
        newNode->redirect_out = -1;
        newNode->next = NULL;

        if (head == NULL)
            head = newNode;
        else
            current->next = newNode;
        current = newNode;
        index++;
    }
    data->commands = head;
    data->num_of_children = index;
    printf("Num of children: %d\n", data->num_of_children);

    while(head)
    {
        printf("Command: %s\n", head->args[0]);
        head = head->next;
    }
    // pipe
   // index = 0;
    // while (index < data->num_of_children - 1)
    // {
    //     if (pipe(data->pipes[index]) == -1)
    //     {
    //         perror("pipe error!!\n");
    //         return (-1);
    //     }
    //     index++;
    // }

    current = head;
    t_cmd *previous = NULL;
    //int i = 0;
    while (current)
    {
        if (previous)
        {
            int p[2];
            pipe(p);
            current->pipe_in = p[PIPE_READ];
            previous->pipe_out = p[PIPE_WRITE];
            // current->pipe_in = data->pipes[i - 1][PIPE_READ];
            // previous->pipe_out = data->pipes[i - 1][PIPE_WRITE];
        }

        previous = current;
        current = current->next;
        //i++;
    }

    while (head)
    {
        printf("PIPE IN: %d\n", head->pipe_in);
        printf("PIPE OUT: %d\n", head->pipe_out);
        head = head->next;
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
