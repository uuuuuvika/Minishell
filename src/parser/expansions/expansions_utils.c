/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:59:00 by darotche          #+#    #+#             */
/*   Updated: 2024/06/26 19:59:52 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

int	is_multi_words(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	replace_for_expansion(char **args, char *cmd)
{
	free(*args);
	*args = ft_strdup(cmd);
}

// might need it for the future
// if (cmd[0] == '$')
// 	{
// 		char *env_name = ft_strdup(cmd + 1);
// 		if (ft_getenv(env_name, data->envs) != NULL)
// 			*args = ft_strdup(ft_getenv(env_name, data->envs));
// 		else
// 			*args = ft_strdup(cmd);
// 		free(env_name);
// 	}