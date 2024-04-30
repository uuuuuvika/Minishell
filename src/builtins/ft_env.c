#include "minishell.h"

void ft_env(t_data data)
{
    // while (data.envp != NULL && *data.envp != NULL)
    // {
    //     printf("%s\n", *data.envp);
    //     data.envp++;
    // }
    execve("/usr/bin/env", data.envp, data.envp);
}