#include "minishell.h"

void ft_exit(t_data *data)
{
	free_arr2D(data->envs->var);
    free_commands(data->commands);
    exit(0);
}
