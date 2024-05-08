#include "minishell.h"

int parse(char *input, t_data *data)
{
    char    *line_copy;
    char    **future_children;
    int     nch;

    //check_NULL(input);
    line_copy = ft_strdup(input);
    check_NULL(line_copy);
    /////////
    sub_dub_quotes(line_copy, data);
    future_children = ft_split(line_copy, '|'); // need to free
    free(line_copy);

    t_cmd *new_node = NULL;
    nch = 0;
    while (future_children[nch])
    {
        new_node = malloc(sizeof(t_cmd));
        new_node->args = ft_split(future_children[nch], ' ');
        new_node->num_args = cnt_args(new_node->args);
        new_node->pipe_in = -1;
        new_node->pipe_out = -1;
        new_node->redirect_in = -1;
        new_node->redirect_out = -1;
        new_node->next = NULL;

        redirect_assign(new_node);
        new_node->args[new_node->num_args] = NULL;

        if (nch++ == 0)
            data->commands = new_node;
        else
        {
            t_cmd *current = data->commands;
            while (current->next)
                current = current->next;
            current->next = new_node;
        }
    }
    data->num_of_children = nch;
    pipe_assign(data->commands);
    return (0);
}
