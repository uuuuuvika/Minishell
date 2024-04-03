#include "minishell.h"

int cpy_envs(t_data *data, t_envs *envs)
{
   // char    **envs_cpy;
    int     i;

    i = 0;
    envs->var = malloc(sizeof(char*) * count_env(data->envp) + 1);
    if (envs->var == NULL)
    {
        perror("Malloc failed");
        exit(1);
    }
    while(data->envp[i] != NULL)
    {   
        envs->var[i] = ft_strdup(data->envp[i]);
        i++;
    }
    envs->var[i] = NULL;

   // i = 0;
    // while (envs->var[i] != NULL)
    // { 
    //     printf("%s\n", envs->var[i]);
    //     i++;
    // }
    return (0);
}