#include "minishell.h"

void ft_unset(t_envs *envs, t_cmd *cmd)
{
    int i;
    int j;
    char **envp;
    char **new_envp;


    i = 0;
    j = 0;
    envp = envs->var;
    while (envs->var[i] != NULL)
    { 
        printf(BLU "%s\n" RESET, envs->var[i]);
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
    free(envs->var);
    envs->var = new_envp;
     i = 0;
    while (envs->var[i] != NULL)
    { 
        printf(GRN "%s\n" RESET, envs->var[i]);
        i++;
    }

   free(new_envp);
}