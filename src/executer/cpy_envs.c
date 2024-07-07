/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:40:26 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 16:01:39 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

int	cpy_envs(t_data *data, char **envp)
{
	int	count;

	print_banner_fun();
	count = 0;
	data->envs = ft_calloc(count_env(envp) + 1, sizeof(char *));
	if (!data->envs)
		return (1);
	while (envp[count])
	{
		data->envs[count] = ft_strdup(envp[count]);
		count++;
	}
	return (0);
}
