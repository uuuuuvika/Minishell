#include "minishell.h"

char    *create_path(char *cmd, t_data *data)
{
    char        *path;
    struct stat statbuf;

    path = ft_strjoin("/bin/", cmd);
    if (stat(path, &statbuf) == 0)
        return (path);
    free(path);
    path = ft_strjoin("/usr/bin/", cmd);
    if (stat(path, &statbuf) == 0)
            return (path);
    free(path);
    printf(YEL "-minishell: %s: command not found \n" WHT, cmd);
    //printf(RED "-minishell: %d: command not found \n" WHT, data->exit_code);
    data->exit_code = 127;
    return (NULL);
}
