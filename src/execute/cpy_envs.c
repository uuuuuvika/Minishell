#include "minishell.h"

int cpy_envs(t_data *data, char **envp)
{
    int i;

    i = 0;
	if(envp == NULL)
		exit(0);
    if (data->envs == NULL) {
        data->envs = malloc(sizeof(t_envs));
        if (data->envs == NULL) {
            perror("Malloc failed");
            exit(1);
        }
        data->envs->var = NULL;
    }
    data->envs->var = malloc(sizeof(char*) * (count_env(envp) + 1));
    if (data->envs->var == NULL)
    {
        perror("Malloc failed");
        exit(1);
    }
    while(envp[i])
    {
        data->envs->var[i] = ft_strdup(envp[i]);
        i++;
    }
    data->envs->var[i] = NULL;
    return (0);
}