#include "minishell.h"

int parse(char *input, t_data *data)
{
    char    *line_copy;
    char    **future_children;
    int     nch;

    //check_NULL(input);

	line_copy = expand_arg(input);
	printf("line_copy: %s\n", line_copy);
	return(0);

    //line_copy = ft_strdup(input);
    check_NULL(line_copy);
    sub_dub_quotes(line_copy, data);
    future_children = ft_split(line_copy, '|'); // need to free
    free(line_copy);
	printf("Continue after expand\n");
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

        int i = 0;
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
            i++;
        }
        new_node->args = realloc(new_node->args, sizeof(char *) * (new_node->num_args + 1));
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
