/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:41:01 by darotche          #+#    #+#             */
/*   Updated: 2024/06/24 15:34:58 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_data *data, char *arg)
{
	int		i;
	char	*env_name;

	i = 0;
	while (data->envs[i] != NULL)
	{
		env_name = get_env_name(data->envs[i], '=');
 		//printf(GRN"env_name: %s\n"RESET, env_name);
		if (ft_strcmp(env_name, arg) == 0)
		{
			free(data->envs[i++]);
			while (data->envs[i] != NULL)
			{
				data->envs[i - 1] = data->envs[i];
				//data->envs[i - 1] = ft_strdup(data->envs[i]);// replaced this line
				i++;
			}
			data->envs[i - 1] = NULL;
			free(env_name);
			return ;
		}
		i++;
		free(env_name);
	}
}

void	ft_unset(t_data *data, t_cmd *cmd, int i)
{
	//int	i;

	i++;
	while (cmd->args[i] != NULL)
	{
		remove_env(data, cmd->args[i]);
		i++;
	}
	data->exit_code = 0;
}
