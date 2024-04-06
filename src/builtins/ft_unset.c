#include "minishell.h"

void ft_unset(t_data *data, t_cmd *cmd)
{
    int i;
    int j;
    int k;
    char **envp;
    char **new_envp;

    i = 0;
    j = 0;
    k = 1;
    envp = data->envs->var;
    new_envp = malloc(sizeof(char*) * (count_env(envp) + 1));
    if (new_envp == NULL) {
        perror("Malloc failed");
        exit(1);
    }
    if (cmd->args[k] == NULL)
        return;
    /// PRINT BEFORE unset
    // while (data->envs->var[i] != NULL)
    // { 
    //     printf(BLU "%s\n" RESET, data->envs->var[i]);
    //     i++;
    // }
    //i = 0;

    //consider checking if the variable exists before attempting to remove it.

    while(cmd->args[k] != NULL)
    {
        i = 0;
        j = 0;
        while (envp[i] != NULL)
        {
            if (ft_strncmp(envp[i], cmd->args[k], ft_strlen(cmd->args[k])) != 0)
            {
                new_envp[j] = ft_strdup(envp[i]);
                j++;
            }
            i++;
        }
        k++;
    }
    new_envp[j] = NULL;
    free(data->envs->var);
    data->envs->var = new_envp;
    //// PRINT AFTER unset
    // i = 0;
    // while (data->envs->var[i] != NULL)
    // { 
    //     printf(GRN "%s\n" RESET, data->envs->var[i]);
    //     i++;
    // }
}