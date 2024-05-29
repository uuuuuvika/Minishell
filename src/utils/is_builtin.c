#include "minishell.h"

// check if the token is a builtin command
int is_builtin(t_cmd *comd)
{
    char *cmd = comd->args[0];
    int i = 0;
    char *builtins[] = {"echo", "cd", "pwd", "env", "exit", "export", "unset", NULL};

    while (builtins[i] != NULL)
    {
        if (strcmp(cmd, builtins[i]) == 0)
        {
            //printf("builtin found: %s\n", token);
            return (1);
        }
        i++;
    }
    return (0);
}
