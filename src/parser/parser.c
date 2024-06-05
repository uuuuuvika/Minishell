#include "minishell.h"

int parse(char *input, t_data *data)
{
    char *line_copy;
    char **future_children;
    int nch;

    //check_NULL(input);

    line_copy = ft_strdup(input);
    //check_NULL(line_copy);
    sub_dub_quotes(line_copy, data);
    sub_sin_quotes(line_copy, data);
    future_children = ft_split(line_copy, '|');
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
        new_node->here_doc = 0;
        new_node->next = NULL;

        return_dub_quotes(new_node->args, data);
        expand_arg(new_node->args, new_node->num_args, data);
        return_sin_quotes(new_node->args, data);

        redirect_assign(new_node, data);
		
		print_2D(new_node->args);
		if (new_node->num_args == 0)
        {
			printf(MAG "num_args: %d\n"RESET, new_node->num_args);
			printf(MAG"!!!!"RESET);
		    free_arr2D(new_node->args);
            free(new_node);
            return (1);
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
    free_arr2D(future_children);
    printf("num_of_children: %d\n", data->num_of_children);
    t_cmd *current = data->commands;
    while (current)
    {
        //printf("cmd: %s\n", current->args[0]);
        printf("num_args: %d\n", current->num_args);
        for (int i = 0; current->args[i]; i++)
            printf("args[%d]: %s\n", i, current->args[i]);
        printf("pipe_in: %d\n", current->pipe_in);
        printf("pipe_out: %d\n", current->pipe_out);
    	   printf("here_doc: %d\n", current->here_doc);
    	   printf("redirect_in: %d\n", current->redirect_in);
    	   printf("redirect_out: %d\n", current->redirect_out);
        current = current->next;
    }
    return (0);
}
