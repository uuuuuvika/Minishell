#include "minishell.h"

char *create_path(char *cmd, t_data *data)
{
    char *path;
    struct stat statbuf;

    path = ft_strjoin("/bin/", cmd);
    if (stat(path, &statbuf) == 0)
    {
		data->exit_code = 0;
        return(path);
    }
    else
    {
        path = ft_strjoin("/usr/bin/", cmd);
        if (stat(path, &statbuf) == 0)
		{
			data->exit_code = 0;
            return(path);
		}
	}
	printf(YEL "-minishell: %s: command not found \n" WHT, cmd);
	data->exit_code = 127;
	return(NULL);
}

