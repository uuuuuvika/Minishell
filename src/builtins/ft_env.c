#include "minishell.h"

void ft_env(t_data *data)
{
    char **envp;

    envp = data->envp;
    if (envp == NULL)
    {
        printf(RED "envp is null\n" RESET);
        return;
    }
    while (*envp != NULL)
    {
        printf("%s\n", *envp);
        envp++;
    }
}