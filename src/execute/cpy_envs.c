#include "minishell.h"

int cpy_envs(t_data *data, char **envp)
{
    int i;

    i = 0;
    if (data->envs == NULL) {
        data->envs = malloc(sizeof(t_envs)); // Allocate memory for t_envs if not already allocated
        if (data->envs == NULL) {
            perror("Malloc failed");
            exit(1);
        }
        data->envs->var = NULL; // Initialize var to NULL
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

////////PRINT COPY
    // i = 0;
    // while (data->envs->var[i] != NULL)
    // { 
    //     printf("%s\n", data->envs->var[i]);
    //     i++;
    // }
    return (0);
}