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
            printf("str: %s\n", str);
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
        while (args[i][j])
        {
            if(args[i][j] == '"' && args[i][j + 1] == '*')
            {
                // size_t len = ft_strlen(args[i]) - 2;
                // if(len == ft_strlen(data->sub[t]))
                // {
                    free(args[i]);
                    args[i] = ft_strdup(data->sub[t]);
                    t++;
               // }
            }
            j++;
                
        }
        i++;
    }
}
