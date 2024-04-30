#include "minishell.h"

void ft_env(t_data *data)
{
    int i;

    i = 0;
    if (data->envs->var == NULL)
    {
        printf(RED "envp is null\n" RESET);
        return;
    }
    while (data->envs->var[i] != NULL)
    { 
        printf("%s\n", data->envs->var[i]);
        i++;
    }
}
