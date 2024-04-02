#include "minishell.h"

void ft_pwd(t_data *data)
{
        (void) data;
        char cwd[MAXPATHLEN];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf( "%s\n", cwd);
        else
        perror("getcwd error");
}