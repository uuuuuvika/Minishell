#include "minishell.h"

void ft_unset(t_data *data, t_cmd *cmd)
{
    int i;
    int j;
    char **envp;
    char **new_envp;

    i = 0;
    j = 0;
    envp = data->envs->var;
    while (data->envs->var[i] != NULL)
    { 
        printf(BLU "%s\n" RESET, data->envs->var[i]);
        i++;
    }
    i = 0;

    if (cmd->args[1] == NULL)
        return;

    new_envp = malloc(sizeof(char*) * (count_env(envp) + 1));
    if (new_envp == NULL) {
        perror("Malloc failed");
        exit(1);
    }
    //consider checking if the variable exists before attempting to remove it.
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], cmd->args[1], ft_strlen(cmd->args[1])) != 0)
        {
            new_envp[j] = ft_strdup(envp[i]);
            j++;
        }
        i++;
    }
    new_envp[j] = NULL;
    free(data->envs->var); // Liberar memoria del arreglo original
    data->envs->var = new_envp;
    ////PRINT AFTER
    // i = 0;
    // while (data->envs->var[i] != NULL)
    // { 
    //     printf(GRN "%s\n" RESET, data->envs->var[i]);
    //     i++;
    // }
}