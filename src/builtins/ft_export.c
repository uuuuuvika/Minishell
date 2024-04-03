#include "minishell.h"

int count_envv(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    return (i);
}

void ft_export(t_data *data, t_cmd *cmd)
{
    int i;
    char **envar;
    char **new_var;

    i = 0;
    envar = data->envp;
    if (cmd->args[1] == NULL)
        return;
    new_var = malloc(sizeof(char*) * (count_envv(envar) + 1));
    if (new_var == NULL)
    {
        perror("Malloc failed");
        exit(1);
    }
    while(envar[i] != NULL)
    {
        new_var[i] = envar[i];
        i++;
    }
    printf(RED "%s" RESET, cmd->args[1]);
    new_var[i] = cmd->args[1];
    i++;
    new_var[i] = NULL;
    data->envp = new_var;
}