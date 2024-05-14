#include "minishell.h"

int count_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
        i++;
   // printf("count_env: %d\n", i);
    return (i);
}
