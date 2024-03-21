#include "minishell.h"

void ft_echo(char *flag, char **str)
{
    while (*str)
    {
        printf("%s", *str);
        str++;
    }
    if (ft_strcmp(flag, "-n") != 0)
        printf("\n");
}