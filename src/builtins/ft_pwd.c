#include "minishell.h"

void ft_pwd()
{
    char cwd[MAXPATHLEN];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    //instead of printing in the stdout, send this to the proper end of the pipe deppending on the next command
    else
    {
        perror("getcwd error");
        exit(0);
    }
    exit (1);
}