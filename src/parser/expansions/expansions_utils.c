/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:59:00 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 17:43:33 by darotche         ###   ########.fr       */
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

int count_dsqm(char **arg)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '$' && (*arg)[i + 1] == '?')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

void	replace_for_expansion(char **args, char *cmd)
{
	free(*args);
	*args = ft_strdup(cmd);
}
