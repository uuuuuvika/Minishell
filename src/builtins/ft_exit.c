#include "minishell.h"

void ft_exit(t_data *data)
{
	free_arr2D(data->envs);
    free_arr2D(data->sub);
    free_data(data);
    //free_commands(data->commands);
    //need to check & free it properly
    //free_commands(data->commands);
    exit(0);
}
