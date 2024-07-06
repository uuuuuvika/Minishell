/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:41:26 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 16:26:30 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_data *data, t_cmd *cmd, int i)
{
	if (ft_strcmp(cmd->args[i], "cd") == 0)
		ft_cd(data, cmd);
	else if (ft_strcmp(cmd->args[i], "echo") == 0)
		ft_echo(data, cmd, i);
	else if (ft_strcmp(cmd->args[i], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(cmd->args[i], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(cmd->args[i], "export") == 0)
		ft_export(data, cmd, i);
	else if (ft_strcmp(cmd->args[i], "unset") == 0)
		ft_unset(data, cmd, i);
	else if (ft_strcmp(cmd->args[i], "exit") == 0)
		ft_exit(data);
}

void	exec_error(char *cmd)
{
	write_error("minishell: ");
	write_error(cmd);
	write_error(": command not found\n");
}

void	exec_cmd(t_data *data, t_cmd *cmd)
{
	char	*path;
	int		i;

	path = NULL;
	// if (cmd->num_args == 0)
	// {
	// 	printf("minishell: : command not found\n");
	// 	return ;
	// }
	i = 0;
	while (ft_strcmp(cmd->args[i], "\0") == 0 && cmd->args[i + 1] != NULL)
		i++;
	if (is_builtin(cmd->args[i]))
		exec_builtin(data, cmd, i);
	else
	{
		//Check if it will be cmd not found or is directory
		path = find_path(cmd->args[i], data);
		if (!path)
		{
			exec_error(cmd->args[i]);
			return ;
		}
		execve(path, &cmd->args[i], data->envs);
		free(path);
	}
}
