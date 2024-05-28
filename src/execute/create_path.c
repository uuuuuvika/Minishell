#include "minishell.h"

char    *create_path(char *cmd, t_data *data)
{
    char        *path;
    struct stat statbuf;
    //printf("cmd: %s\n", cmd);
    if (strcmp(cmd, "") == 0)
        printf("-minishell: : command not found \n"); // This is a bit of a cheat code, if we have time we should make it better :)
    path = ft_strjoin("/bin/", cmd);
    if (stat(path, &statbuf) == 0)
        return (path);
    free(path);
    path = ft_strjoin("/usr/bin/", cmd);
    if (stat(path, &statbuf) == 0)
            return (path);
    free(path);
    printf("-minishell: %s: command not found \n", cmd); // Do Not delete this line
    data->exit_code = 127;
    return (NULL);
}
