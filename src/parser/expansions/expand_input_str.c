#include "minishell.h"

char *expand_line(char *line, t_data *data)
{
    char **split = ft_split(line, ' ');
    int i = 0;
    while(split[i])
    {
        //printf("split[%d]: %s\n", i, split[i]);
        if(split[i][0] == '$')
        {
            char *env = ft_getenv(split[i] + 1, data->envs);
            if(env)
            {
                free(split[i]);
                split[i] = ft_strdup(env);
            }
        }
        i++;
    }
    char *new_line = arr2D_to_str(split);
    return (new_line);
}