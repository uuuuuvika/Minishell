#include "minishell.h"

void	print_envs(t_data *data)
{
    int i;

	i = 0;
    while (data->envs->var[i] != NULL)
    { 
        printf(GRN "%s\n" RESET, data->envs->var[i]);
        i++;
    }
}