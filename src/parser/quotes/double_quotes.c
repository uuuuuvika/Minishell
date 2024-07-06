#include "minishell.h"

int get_quoted_substr(char *line_copy, char *str, int index)
{
    int str_index;
    
    str_index = 0;
    while (line_copy[++index] != '"')
    {
        str[str_index++] = line_copy[index];
        line_copy[index] = '*';
    }
    return index;
}

void sub_d_quotes(char *line_copy, t_data *data)
{
    int index = 0;
    int s_index = 0;
    int len;
    char *str;

    while (line_copy[index])
    {
        if (line_copy[index] == '"')
        {
            len = word_len(line_copy, index, "\"");
            str = ft_calloc(len, sizeof(char));
            index = get_quoted_substr(line_copy, str, index);
            data->sub[s_index++] = ft_strdup(str);
            free(str);
        }
        index++;
    }
    data->sub[s_index] = NULL;
}

int sub_dub_quotes(char *line_copy, t_data *data)
{
    int count_subs;

    count_subs = count_quotes(line_copy, "\"");
    if (handle_odd_quotes(count_subs, data, "\""))
        return 1;
    data->sub = malloc(((count_subs / 2) + 1) * sizeof(char *));
    sub_d_quotes(line_copy, data);
    return (0);
}

void return_dub_quotes(char **args, t_data *data)
{
    int i;
    int t;
    int j;
    char *tmp;

    i = 0;
    t = 0;
    while (args[i])
    {
        j = 0;
        handle_empty_quotes(args[i], "\"");
        while (args[i][j])
        {
            if (args[i][j] == '"' && args[i][j + 1] == '*')
            {
                tmp = malloc((j + 2) * sizeof(char));
                ft_strlcpy(tmp, args[i], j + 1);
                free(args[i]);
                args[i] = ft_strjoin(tmp, data->sub[t++]);
            }
            j++;
        }
        i++;
    }
}
