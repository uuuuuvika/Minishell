#include "../minishell.h"

void ft_echo(char *flag, char **str)
{
    while (*str)
    {
        printf("%s", *str);
        str++;
    }
    if (flag == NULL)
        printf("\n");
    //exit(0);
}