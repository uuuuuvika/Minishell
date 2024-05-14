#include "minishell.h"

int cpy_envs(t_data *data, char **envp)
{
    int count;

    //data->envs = ft_calloc(count_env(envp) + 1, sizeof(char *));
    data->envs = malloc(sizeof(char *) * (count_env(envp) + 1));

    if (!data->envs)
    {
        perror("Calloc failed");
        return (1);
    }
    count = 0;
    while (envp[count])
    {
        data->envs[count] = ft_strdup(envp[count]);
        count++;
    }
    data->envs[count] = NULL;
    //printf("cpy_envs: %d\n", count);
   // data->envs[count] = ft_strdup("asdaadad");
    return (0);
}