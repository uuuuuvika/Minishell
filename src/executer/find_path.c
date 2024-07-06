/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:40:19 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 21:50:38 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_path(char *cmd, char **paths, struct stat statbuf)
{
	int		i;
	char	*path;
	char	*tmp_path;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin_nf(paths[i], "/");
		path = ft_strjoin(tmp_path, cmd);
		if (stat(path, &statbuf) == 0)
		{
			free_arr2D(paths);
			return (path);
		}
		free(path);
		i++;
	}
	return (0);
}

char	*check_rel_path(char *cmd, t_data *data, struct stat statbuf)
{
	char	*path;
	char	**paths;
	char	*env_path;

	env_path = ft_getenv("PATH", data->envs);
	if (env_path == NULL)
	{
		data->exit_code = 127;
		return (NULL);
	}
	paths = ft_split(env_path, ':');
	free(env_path);
	path = create_path(cmd, paths, statbuf);
	if (path != 0)
		return (path);
	free_arr2D(paths);
	return (NULL);
}

char	*check_abs_path(char *cmd, t_data *data, struct stat statbuf)
{
	if (ft_strchr(cmd, '/') == NULL)
		return (NULL);
	if (stat(cmd, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			errno = EISDIR;
			perror(cmd);
			data->exit_code = 126;
			return (cmd);
		}
		else if (statbuf.st_mode & S_IXUSR)
			return (cmd);
		else
		{
			errno = EACCES;
			perror("-minishell");
			data->exit_code = 126;
			return (cmd);
		}
	}
	data->exit_code = 127;
	errno = ENOENT;
	perror("-minishell");
	return (cmd);
}

char	*find_path(char *cmd, t_data *data)
{
	struct stat	statbuf;
	char		*path;

	statbuf.st_mode = 0;
	path = NULL;
	// if (ft_strcmp(cmd, "") == 0)
    // {
    //     errno = ENOENT; // No such file or directory
    //     perror("-minishell");
    // }
	path = check_abs_path(cmd, data, statbuf);
	if (path != NULL)
		return (path);
	path = check_rel_path(cmd, data, statbuf);
	if (path != NULL)
	{
		if (ft_strcmp(cmd, "") == 0)
			data->exit_code = 0;
		return (path);
	}
	//  write_error("minishell: ");
    // // write_error(cmd);
    // //write_error(": command not found\n");
    // errno = ENOENT;
    // perror("-minishell");
    // printf(BLU "-minishell: %s: Command not found\n" RESET, cmd);
	data->exit_code = 127;
	return (NULL);
}
