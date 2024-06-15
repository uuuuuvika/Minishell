#include "minishell.h"

// char *find_path(char *cmd, t_data *data)
// {
// 	char *path;
// 	char **paths;
// 	struct stat statbuf;
// 	printf("cmd: %s\n", cmd);

// 	// if (stat(cmd, &statbuf) == 0)
// 	// {
// 	// 	printf("lollll cmd: %s\n", cmd);
// 	// 	return (cmd);
// 	// }
// 	if (ft_strcmp(cmd, "") == 0)
// 		printf("-minishell: : command not found \n"); // This is a bit of a cheat code, if we have time we should make it better :)
	
// 	paths = ft_split(ft_getenv("PATH", data->envs), ':');

// 	int i = 0;
// 	while (paths[i])
// 	{
// 		paths[i] = ft_strjoin_nf(paths[i], "/");
// 		paths[i] = ft_strjoin_nf(paths[i], cmd);
// 		if (stat(paths[i], &statbuf) == 0)
// 		{
// 			path = ft_strdup(paths[i]);
// 			free_arr2D(paths);
// 			return (path);
// 		}
// 		i++;
// 	}
// 	//printf(BLU "-minishell: %s: command not found \n" RESET, cmd); // This error is for commands														   // add printferror for ("-minishell: %s: No such file or directory \n", cmd), there are some errors "Permision denied" w exit code 126(cmd found but not executable)
// 	data->exit_code = 127;
// 	return (NULL);
// }


char *check_abs_path(char *cmd, t_data *data)
{
    struct	stat statbuf;

    if (stat(cmd, &statbuf) == 0)
    {
        if (S_ISDIR(statbuf.st_mode))
        {
            errno = EISDIR; // Is a directory
        	perror(cmd);
            data->exit_code = 126;
            return (cmd);
        }
        else if (statbuf.st_mode & S_IXUSR)
            return (cmd); // Command is executable
        else
        {
            errno = EACCES; // Permission denied
            perror(cmd);
            data->exit_code = 126;
            return (cmd);
        }
    }
    return (NULL);
}

char *check_rel_path(char *cmd, t_data *data)
{
    struct	stat statbuf;
    char	*path;
    char	**paths;
    int		i;

    paths = ft_split(ft_getenv("PATH", data->envs), ':');
    i = 0;
    while (paths[i])
    {
        path = ft_strjoin_nf(paths[i], "/");
        path = ft_strjoin_nf(path, cmd);
        if (stat(path, &statbuf) == 0)
        {
            free_arr2D(paths);
            return(path);
        }
        free(path);
        i++;
    }
    free_arr2D (paths);
    return (NULL);
}

char	*find_path(char *cmd, t_data *data)
{
	char	*path;

    if (ft_strcmp(cmd, "") == 0)
    {
        errno = ENOENT; // No such file or directory
        perror("-minishell");
        data->exit_code = 127;
        return (NULL);
    }
	path = check_abs_path(cmd, data);
    if (path != NULL)
		return (path);
	path = check_rel_path(cmd, data);
	if (path != NULL)
		return (path);
	errno = ENOENT;
	//printf(BLU "-minishell: %s: Command not found\n" RESET, cmd);
	perror(cmd);
	data->exit_code = 127;
    return (NULL);
}