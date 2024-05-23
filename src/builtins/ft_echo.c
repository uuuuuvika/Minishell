#include "minishell.h"

//TRY: echo -n $USER

void ft_echo(t_data *data, t_cmd *cmd)
{
    (void) data;
    int i;

    i = 1;

    while (cmd->args && ft_strcmp(cmd->args[i], "-n") == 0) 
        i++;
    while (cmd->args[i])
    {
        if (!cmd->args[i])
            return ;
        ft_printf("%s", cmd->args[i]);
        i++;
        if (cmd->args[i] != NULL)
            ft_printf(" ");
    }
    if (ft_strcmp(cmd->args[1], "-n") != 0)
        ft_printf("\n");
}