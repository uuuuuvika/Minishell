#include "minishell.h"

void ft_exit(t_data *data)
{
	free_arr2D(data->envs);
    free_arr2D(data->sub);
    free_arr2D(data->subb);
    free_data(data);
    clear_history();
    //need to check & free it properly
    exit(0);
}
