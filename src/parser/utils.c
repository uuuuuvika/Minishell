#include "minishell.h"

void sub_quot(char *line_copy, t_data *data)
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
    printf("Count subs: %d\n", count_subs / 2);

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