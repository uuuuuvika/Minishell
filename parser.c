#include "minishell.h"

int parse(char *input, t_data *data)
{
    char *line_copy;
    char **future_children;
    char str[20];

    if (input == NULL)
    {
        printf("Error! Input is NULL.\n");
        return -1;
    }

    line_copy = strdup(input);

    if (line_copy == NULL)
    {
        printf("Error!\n");
        return -1;
    }

    data->sub = malloc(10 * sizeof(char **));
    data->commands = malloc(10 * sizeof(t_command));

    //printf("LINE COPY ----> %s\n", line_copy);

    int index = 0;
    int s_index = 0;
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
    //printf("LINE COPY ----> %s\n", line_copy);

    future_children = ft_split(line_copy, '|');

    index = 0;
    while (future_children[index])
    {
        data->num_of_children++;
        data->commands[index].args = ft_split(future_children[index], ' ');
        index++;
    }
    // printf("CHILDREN: %d\n", data->num_of_children);
    
    // int i = 0;
    // while (i < data->num_of_children)
    // {
    //     //printf("CHILDREN [%d]: %s\n",i, data->commands[i].cmd);
    //     int j = 0;
    //     while (data->commands[i].args[j])
    //     {
    //         printf("CHILDREN [%d]: %s\n",i, data->commands[i].args[j]);
    //         j++;
    //     }
    //     i++;
    // }

    return (0);
}
