#include "minishell.h"

int count_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    return (i);
}

void ft_unset(t_data *data, t_cmd *cmd)
{
    int i;
    int j;
    char **envp;
    char **new_envp;

    i = 0;
    j = 0;
    envp = data->envp;
    if (cmd->args[1] == NULL)
        return;

    new_envp = malloc(sizeof(char*) * (count_env(envp) + 1));
    if (new_envp == NULL) {
        perror("Malloc failed");
        exit(1);
    }

    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], cmd->args[1], ft_strlen(cmd->args[1])) != 0)
        {
            new_envp[j] = envp[i];
            j++;
        }
        i++;
    }
    new_envp[j] = NULL;
    data->envp = new_envp;
}