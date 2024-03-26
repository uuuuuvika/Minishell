#include "minishell.h"

int check_NULL(char *str)
{
    if (str == NULL)
    {
        printf("Error: %s\n", str);
        return -1;
    }
    return 0;
}