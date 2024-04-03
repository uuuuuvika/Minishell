#include "minishell.h"

int count_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    return (i);
}
