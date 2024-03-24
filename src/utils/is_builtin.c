#include "minishell.h"

//check if the token is a builtin command
int is_builtin(char *token)
{
    int i = 0;
    char *builtins[] = {"echo", "cd", "pwd", "env", "exit", "export", "unset", NULL};

    while (builtins[i] != NULL)
    {
        if (strcmp(token, builtins[i]) == 0)
        {
            return (1);
        }
        i++;
    }
    return (0);
}