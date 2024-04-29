#include "minishell.h"

void ft_exit(t_data *data)
{
    free_data(data);
    exit(0);
}