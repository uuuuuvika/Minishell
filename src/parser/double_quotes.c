#include "minishell.h"

void sub_dub_quotes(char *line_copy, t_data *data)
{
    int index = 0;
    int count_subs = 0;
    while (line_copy[index])
    {
        if (line_copy[index] == '"')
            count_subs++;
        index++;
    }
    if (count_subs % 2 != 0)
    {
        char *del = "\"";
        read_heredoc_simple(del, data);
        return;
    }

    data->sub = malloc((count_subs / 2) * sizeof(char *));
    int s_index = 0;
    index = 0;
    while (line_copy[index])
    {
        if (line_copy[index] == '"')
        {
            int k = index;
            while (line_copy[++k] != '"')
                ;
            int len = k - index;
            char *str = calloc(len, sizeof(char));
            int str_index = 0;
            while (line_copy[++index] != '"')
            {
                str[str_index++] = line_copy[index];
                line_copy[index] = '*';
            }
            data->sub[s_index++] = ft_strdup(str);
        }
        index++;
    }
    data->sub[s_index] = NULL;
}

void return_dub_quotes(char **args, t_data *data)
{
    int i = 0;
    int t = 0;
    while (args[i])
    {
        if (args[i][0] == '"' && args[i][1] == '*')
        {
            free(args[i]);
            args[i] = ft_strdup(data->sub[t]);
            t++;
        }
        else if (args[i][0] == '"' && args[i][1] == '"')
            args[i][0] = '\0';
        i++;
    }
}
