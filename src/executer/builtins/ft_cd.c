/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:19 by darotche          #+#    #+#             */
/*   Updated: 2024/07/02 15:22:04 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ch_env_pwd(t_data *data, char *new_pwd, char *old_pwd)
{
	int	i;

	i = 0;
	while (data->envs[i] != NULL)
	{
		if (ft_strncmp(data->envs[i], "PWD=", 4) == 0)
		{
			free(data->envs[i]);
			data->envs[i] = ft_strjoin_nf("PWD=", new_pwd); 
		}
		else if (ft_strncmp(data->envs[i], "OLDPWD=", 7) == 0)
		{
			free(data->envs[i]);
			data->envs[i] = ft_strjoin_nf("OLDPWD=", old_pwd);
		}
		i++;
	}
}

void	cd_handle_error(t_data *data, char *old_pwd)
{
	write_error("minishell: cd: ");
	write_error("too many arguments\n");
	data->exit_code = 1;
	free(old_pwd);
}

void	handle_chdir_error(t_data *data, char *arg, char *old_pwd)
{
	perror(arg);
	data->exit_code = 1;
	free(old_pwd);
}

char	*get_new_pwd(char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("Failed to get current directory");
		free(old_pwd);
		return (NULL);
	}
	return (new_pwd);
}

void	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		perror("Failed to get current directory");
		return ;
	}
	if (cmd->num_args > 2)
	{
		cd_handle_error(data, old_pwd);
		return ;
	}
	if (cmd->args[1] == NULL || cmd->args[1][0] == '~')
		chdir(getenv("HOME"));
	else if (chdir(cmd->args[1]) != 0)
	{
		handle_chdir_error(data, cmd->args[1], old_pwd);
		return ;
	}
	if (get_new_pwd(old_pwd) == NULL)
		return ;
	ch_env_pwd(data, get_new_pwd(old_pwd), old_pwd);
	free(old_pwd);
}
