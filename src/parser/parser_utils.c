#include "minishell.h"

void sub_dub_quotes(char *line_copy, t_data *data)
{
    char str[20];
    int index = 0;
    int count_subs = 0;

    while (line_copy[index])
    {
        if (line_copy[index] == '"')
            count_subs++;
        index++;
    }

    data->sub = malloc((count_subs / 2) * sizeof(char *));

    int s_index = 0;
    index = 0;
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
}


int cnt_args(char **args)
{
    int i = 0;
    while (args[i] && !is_redir(args[i]))
        i++;
    return (i);
}

void pipe_assign(t_cmd *command)
{
    int p[2];
    t_cmd *current = command;
    t_cmd *previous = NULL;
    while (current)
    {
        if (previous)
        {
            pipe(p);
            previous->pipe_out = p[PIPE_WRITE];
            current->pipe_in = p[PIPE_READ];
        }
        previous = current;
        current = current->next;
    }
}

