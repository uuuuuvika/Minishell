#include "minishell.h"

void	print_envs(t_data *data)
{
    int i;

	i = 0;
    while (data->envs[i] != NULL)
    { 
        printf(GRN "%s\n" RESET, data->envs[i]);
        i++;
    }
}