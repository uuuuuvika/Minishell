#include "minishell.h"

char *create_path(char *cmd)
{
    char *path;
    struct stat statbuf;

    path = ft_strjoin("/bin/", cmd);
    if (stat(path, &statbuf) == 0)
    {
        printf(GRN"%s exists, returns path\n"RESET, path);
        return(path);
    }
    else
    {
        path = ft_strjoin("/usr/bin/", cmd);
        if (stat(path, &statbuf) == 0)
        {
            printf(GRN"%s exists, returns path\n"RESET, path);
            return(path);
        }
    }
    printf(RED"%s do not exists, returns null \n"RESET, path);
    return (NULL);
}