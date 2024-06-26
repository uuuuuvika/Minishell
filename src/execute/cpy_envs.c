/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:40:26 by darotche          #+#    #+#             */
/*   Updated: 2024/06/26 20:55:59 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cpy_envs(t_data *data, char **envp)
{
	int	count;

	data->envs = ft_calloc(count_env(envp) + 1, sizeof(char *));
	if (!data->envs)
	{
		perror(RED "ft_calloc failed\n" RESET);
		return (1);
	}
	count = 0;
	while (envp[count])
	{
		data->envs[count] = ft_strdup(envp[count]);
		count++;
	}
	return (0);
}
