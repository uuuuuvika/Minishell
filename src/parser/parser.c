#include "minishell.h"

int parse(char *input, t_data *data)
{
    char *line_copy;
    char **future_children;
    int index;

    check_NULL(input);
    line_copy = strdup(input);
    check_NULL(line_copy);

    sub_dub_quotes(line_copy, data);

    future_children = ft_split(line_copy, '|');
    free(line_copy);

    t_cmd *current = NULL;
    index = 0;
    while (future_children[index])
    {
        t_cmd *new_node = malloc(sizeof(t_cmd));
        new_node->args = ft_split(future_children[index], ' ');
        new_node->num_args = 0;
        new_node->pipe_in = -1;
        new_node->pipe_out = -1;
        new_node->redirect_in = -1;
        new_node->redirect_out = -1;
        new_node->next = NULL;

        int i = 0;
        while (new_node->args[i] && ft_strcmp(new_node->args[i], ">") != 0 && ft_strcmp(new_node->args[i], "<") != 0 && ft_strcmp(new_node->args[i], "<<") != 0 && ft_strcmp(new_node->args[i], ">>") != 0)
        {
            new_node->num_args++;
            i++;
        }
        i = 0;
        while (new_node->args[i])
        {
            if (ft_strcmp(new_node->args[i], ">") == 0)
            {
                new_node->redirect_out = open(new_node->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                i++;
            }
            else if (ft_strcmp(new_node->args[i], "<") == 0)
            {
                new_node->redirect_in = open(new_node->args[i + 1], O_RDONLY);
                i++;
            }
            else if (ft_strcmp(new_node->args[i], ">>") == 0)
            {
                new_node->redirect_out = open(new_node->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                i++;
            }
            // else if (ft_strcmp(new_node->args[i], "<<") == 0)
            // {
            //     here we need to implement the here_doc function
            //     new_node->redirect_in = here_doc(new_node->args[i + 1]);
            //     i++;
            // }
            i++;
        }
        new_node->args = realloc(new_node->args, sizeof(char *) * (new_node->num_args + 1));
        new_node->args[new_node->num_args] = NULL;

        // i = 0;
        // while(new_node->args[i])
        // {
        //     printf("args[%d]: %s\n", i, new_node->args[i]);
        //     i++;
        // }
        if (index++ == 0)
            data->commands = new_node;
        else
            current->next = new_node;
        current = new_node;
    }
    data->num_of_children = index;

    current = data->commands;
    t_cmd *previous = NULL;
    while (current)
    {
        if (previous)
        {
            int p[2];
            pipe(p);
            previous->pipe_out = p[PIPE_WRITE];
            current->pipe_in = p[PIPE_READ];
        }
        previous = current;
        current = current->next;
    }

    // current = data->commands;
    // while (current)
    // {
    //     printf("num_args: %d\n", current->num_args);
    //     printf("redirect_in: %d\n", current->redirect_in);
    //     printf("redirect_out: %d\n", current->redirect_out);
    //     previous = current;
    //     current = current->next;
    // }
    return (0);
}
