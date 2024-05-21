#include "minishell.h"

void ft_echo(t_data *data, t_cmd *cmd)
{
    (void) data;
    int i;

    i = 1;
    //printf(YEL"Executing builtin echo\n" RESET);
    while (cmd->args[i])
    {
        if (i > 1)
            printf(" ");
        if (ft_strcmp(cmd->args[i], "-n") == 0 && !cmd->args[i + 1])
            return ;
        if (ft_strcmp(cmd->args[i], "-n") == 0) 
            i++;
        printf("%s", cmd->args[i]);
        i++;
    }
    if (ft_strcmp(cmd->args[1], "-n") != 0)
        printf("\n");
}