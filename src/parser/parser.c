#include "minishell.h"

int parse(char *input, t_data *data)
{
    char    *line_copy;
    char    **future_children;
    int     nch;

    check_NULL(input);

    line_copy = ft_strdup(input);
    check_NULL(line_copy);
	sin_quotes(line_copy);
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
		
        expand_arg(new_node->args, new_node->num_args, data);
        redirect_assign(new_node);

        new_node->args = realloc(new_node->args, sizeof(char *) * (new_node->num_args + 1));
        new_node->args[new_node->num_args] = NULL;

        return_dub_quotes(new_node->args, data);
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
    // printf("num_of_children: %d\n", data->num_of_children);
    pipe_assign(data->commands);

    // t_cmd *current = data->commands;
    // while (current)
    // {
    //     printf("cmd: %s\n", current->args[0]);
    //     printf("pipe_in: %d\n", current->pipe_in);
    //     printf("pipe_out: %d\n", current->pipe_out);
    //     printf("redirect_in: %d\n", current->redirect_in);
    //     printf("redirect_out: %d\n", current->redirect_out);
    //     current = current->next;
    // }
    return (0);
}
