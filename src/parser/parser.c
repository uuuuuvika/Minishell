
#include "minishell.h"

int parse(char *input, t_data *data)
{
    char *line_copy;
    char **future_children;
    int nch;

    // check_NULL(input);
    line_copy = ft_strdup(input);
    // check_NULL(line_copy);
    sub_dub_quotes(line_copy, data);
    sub_sin_quotes(line_copy, data);
    future_children = ft_split(line_copy, '|');
    free(line_copy);

    t_cmd *new_node = NULL;
    nch = 0;
    //char *expanded;
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
        int i = 0;
        while (new_node->args[i])
        {
            if (ft_strcmp(new_node->args[i], "<<") == 0)
            {
                if (new_node->args[i + 1] == NULL)
                {
                    free_arr2D(new_node->args);
                    free(new_node);
                    printf("Error: syntax error near unexpected token `newline'\n");
                    return (1);
                }
                else if (new_node->args[i + 1][0] == '\'' || new_node->args[i + 1][0] == '\"')
                    new_node->here_doc_exp = 0;
                else
                    new_node->here_doc_exp = 1;
            }
            i++;
        }

        return_dub_quotes(new_node->args, data);
		
		expand_arg(new_node->args, new_node->num_args, data);
		// Replaced `void expand_arg` to `char	*expand_arg()`
        //expanded = expand_arg(new_node->args, new_node->num_args, data);
		//// Call parser recursively to handle $COMPLEXCMD etc.
        //
		// if (ft_strncmp(input, "$", 1) == 0) //// We need to find the proper way to call this. Now calls when input is '$'
		// {
		// 	char *tmp = ft_strdup(expanded);
		// 	free_arr2D(new_node->args);
		// 	free(new_node);
		// 	printf(MAG"tmp: %s\n"RESET, tmp);	//// Need to free
	    // 	parse(tmp, data);
		// }

		return_sin_quotes(new_node->args, data);
        redirect_assign(new_node, data);
		
		print_2D(new_node->args);///////////////
		if (new_node->num_args == 0)
        {
			printf(MAG "num_args: %d\n"RESET, new_node->num_args);//////////
		    free_arr2D(new_node->args);
            free(new_node);
            return (1);
        }

        new_node->args = realloc(new_node->args, sizeof(char *) * (new_node->num_args + 1));
        new_node->args[new_node->num_args] = NULL;

        if (nch++ == 0)
		{
            data->commands = new_node;
			print_2D(data->commands->args);
		}
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
    // printf("num_of_children: %d\n", data->num_of_children);
    //  t_cmd *current = data->commands;
    //  while (current)
    //  {
    //      // printf("cmd: %s\n", current->args[0]);
    //      printf("num_args: %d\n", current->num_args);
    //      for (int i = 0; current->args[i]; i++)
    //          printf("args[%d]: %s\n", i, current->args[i]);
    //      // printf("pipe_in: %d\n", current->pipe_in);
    //      // printf("pipe_out: %d\n", current->pipe_out);
    //      // printf("here_doc: %d\n", current->here_doc);
    //      // printf("redirect_in: %d\n", current->redirect_in);
    //      // printf("redirect_out: %d\n", current->redirect_out);
    //      current = current->next;
    //  }
    return (0);
}


