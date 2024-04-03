#include "minishell.h"

void ft_exit(t_data *data, t_cmd *cmd)
{
    free_data(data);
    free_commands(cmd);
    exit(0);
}