#include "minishell.h"

//check if the token is a builtin command
int is_builtin(t_cmd *command)
{
    char *token = command->args[0];
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
