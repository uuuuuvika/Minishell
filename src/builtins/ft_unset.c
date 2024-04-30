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
}