#include "minishell.h"

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

int parse_input(char *input)
{
    char *line_copy;
    char *token;

    if (input == NULL)
    {
        printf("Error! Input is NULL.\n");
        return -1;
    }

    line_copy = strdup(input);

    if (line_copy == NULL)
    {
        printf("Error!\n");
        return -1;
    }

    token = strtok(line_copy, " \t\n\r");

    while (token != NULL)
    {
        printf("%s\n", token);

        if (is_builtin(token))
        {
            printf(RED "Found a builtin command --> %s\n" RESET, token);
            // execute_builtin(token);
        }

        if (strcmp(token, "|") == 0)
            printf(RED "Found a pipe!\n" RESET);

        token = strtok(NULL, " \t\n\r");
    }

    free(line_copy);
    return 0;
}