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

    data->sub = malloc(((count_subs / 2) + 1) * sizeof(char *));
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
        int j = 0;
        if (args[i][0] == '"' && args[i][1] == '"')
            args[i][0] = '\0';
        else
        {
            while (args[i][j])
            {
                if (args[i][j] == '"' && args[i][j + 1] == '*')
                {
                    char *tmp = malloc((j + 2) * sizeof(char));
                    ft_strlcpy(tmp, args[i], j + 1);
                    // printf("tmp: %s\n", tmp);
                    free(args[i]);
                    args[i] = ft_strjoin(tmp, data->sub[t]);
                    t++;
                }
                j++;
            }
        }
        i++;
    }
}
