#include "../minishell.h"

void ft_pwd()
{
    char cwd[MAXPATHLEN];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
    {
        perror("getcwd error");
        exit(0);
    }
}