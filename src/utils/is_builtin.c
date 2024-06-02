#include "minishell.h"

int is_builtin(char *cmd)
{
    int i;
    char *builtins[] = {"echo", "cd", "pwd", "env", "exit", "export", "unset", NULL};
    i = 0;
    while (builtins[i] != NULL)
    {
        if (ft_strcmp(cmd, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}
