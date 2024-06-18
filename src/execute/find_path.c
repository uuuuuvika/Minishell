/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:40:19 by darotche          #+#    #+#             */
/*   Updated: 2024/06/18 19:52:13 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
            data->exit_code = 127;
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
	char	*env_path;
	
    int		i;

	path = NULL;
	paths = NULL;
	env_path = ft_getenv("PATH", data->envs);
    paths = ft_split(env_path, ':');
	free (env_path);
    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(path, cmd);
        if (stat(path, &statbuf) == 0)
        {
            free_arr2D(paths);
            return(path);
        }
        free(path);
        i++;
    }
//    free (path);
	return (NULL);
}

char	*find_path(char *cmd, t_data *data)
{
	char	*path;

	path = NULL;
    if (ft_strcmp(cmd, "") == 0)
    {
        //errno = ENOENT; // No such file or directory
        //perror("-minishell");
    //    data->exit_code = 127;
        return (NULL);
    }
	path = check_abs_path(cmd, data);
    if (path != NULL)
		return (path);
	path = check_rel_path(cmd, data);
	if (path != NULL)
		return (path);
	// write_error("minishell: ");
	// write_error(cmd);
	// write_error(": command not found\n");
	//errno = "Command nt found";
//	perror("");
	//printf(BLU "-minishell: %s: Command not found\n" RESET, cmd);
	data->exit_code = 127;
	//free(path);
    return (NULL);
}
