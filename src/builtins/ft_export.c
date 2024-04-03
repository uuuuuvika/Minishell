#include "minishell.h"

void ft_export(t_data *data, t_cmd *cmd)
{
    int     i;
    int     j;
    char    **envar;
    char    **new_var;

    i = 0;
    j = 1;
    envar = data->envp;
    check_NULL(cmd->args[1]); //neeed to check args format as well
    new_var = malloc(sizeof(char*) * (count_env(envar) + 2));
    if (new_var == NULL)
    {
        perror("Malloc failed");
        exit(1);
    }
    while(cmd->args[j] != NULL)
    {
        while(envar[i] != NULL)
        {
            new_var[i] = envar[i];
            i++;
        }
        new_var[i] = cmd->args[j];
        i++;
        new_var[i] = NULL;
        j++;
    }
    data->envp = new_var;
}