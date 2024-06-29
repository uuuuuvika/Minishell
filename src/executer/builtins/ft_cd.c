/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:19 by darotche          #+#    #+#             */
/*   Updated: 2024/06/27 17:08:21 by darotche         ###   ########.fr       */
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

void	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		perror("Failed to get current directory");
		return ;
	}
	if(cmd->num_args > 2)
	{
		write_error("minishell: cd: ");
		write_error("too many arguments\n");
		data->exit_code = 1;
		free(old_pwd);
		return ;
	}
    if (cmd->args[1] == NULL || cmd->args[1][0] == '~')
		chdir(getenv("HOME"));
    else if (chdir(cmd->args[1]) != 0)
    {
        perror(cmd->args[1]);
		data->exit_code = 1;
        free(old_pwd);
        return ;
    }
    new_pwd = getcwd(NULL, 0);
    if (new_pwd == NULL)
    {
        perror("Failed to get current directory");
        free(old_pwd);
        return ;
    }
    ch_env_pwd(data, new_pwd, old_pwd);
    free(new_pwd);
    free(old_pwd);
}
