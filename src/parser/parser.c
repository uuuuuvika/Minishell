
#include "minishell.h"

void args_realloc(t_cmd *new_node)
{
    char **temp;
    int i;

    temp = malloc(sizeof(char *) * (new_node->num_args + 1));
    i = 0;
    while (i < new_node->num_args)
    {
        temp[i] = ft_strdup(new_node->args[i]);
        i++;
    }
    temp[i] = NULL;
    free_arr2D(new_node->args);
    new_node->args = temp;
}

int handle_redirects(t_cmd *new_node, t_data *data, char **future_children)
{
    int j;

    j = redirect_assign(new_node, data);
    if (j != 0)
    {
        free_arr2D(new_node->args);
        free(new_node);
        free_arr2D(future_children);
        free_arr2D(data->sub);
        free_arr2D(data->subb);
        data->exit_code = j;
        return (1);
    }
    return (0);
}

static void add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_node)
{
    t_cmd *current;

    current = NULL;
    if (*cmd_list == NULL)
        *cmd_list = new_node;
    else
    {
        current = *cmd_list;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
}

static t_cmd *create_cmd_node(char *cmd_str)
{
    t_cmd *new_node;

    new_node = malloc(sizeof(t_cmd));
    new_node->args = ft_split(cmd_str, ' ');
    new_node->num_args = cnt_args(new_node->args);
    new_node->pipe_in = -1;
    new_node->pipe_out = -1;
    new_node->redirect_in = -1;
    new_node->redirect_out = -1;
    new_node->here_doc = 0;
    new_node->next = NULL;
    return (new_node);
}

char *refine_input_line(char *input, t_data *data)
{
    char *clean_and_expanded_line;
    char *line_copy;

    if (sub_quotes(input, data))
        return (NULL);
    line_copy = replace_tabs_with_spaces(input);
    char *line_copy_2 = handle_missing_spaces(line_copy);
    clean_and_expanded_line = expand_line(line_copy_2, data);
    free(line_copy);
    return (clean_and_expanded_line);
}

int parse(char *input, t_data *data)
{
    char **future_children;
    t_cmd *new_node;
    int nch;
    char *expanded_line;

    expanded_line = refine_input_line(input, data);
    if (!expanded_line)
        return (1);
    future_children = ft_split(expanded_line, '|');
    free(expanded_line);
    new_node = NULL;
    nch = 0;
    while (future_children[nch])
    {
        new_node = create_cmd_node(future_children[nch]);
        if (heredoc_preprocess(new_node, data))
            return (1);
        return_dub_quotes(new_node->args, data);
        expand_arg(new_node->args, data);
        return_sin_quotes(new_node->args, data);
        if (handle_redirects(new_node, data, future_children))
            return (1);
        args_realloc(new_node);
        add_cmd_to_list(&(data->commands), new_node);
        nch++;
    }
    data->num_of_children = nch;
    pipe_assign(data->commands);
    free_arr2D(future_children);
    return (0);
}
