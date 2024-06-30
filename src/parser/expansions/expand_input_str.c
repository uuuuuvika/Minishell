/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:22:47 by darotche          #+#    #+#             */
/*   Updated: 2024/06/26 19:56:22 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_line(char *line, t_data *data)
{
	char	**split;
	char	*env;
	char	*new_line;
	int		i;

	split = ft_split(line, ' ');
	i = 0;
	while (split[i])
	{
		if (split[i][0] == '$')
		{
			env = ft_getenv(split[i] + 1, data->envs);
			if (env)
			{
				replace_for_expansion(&split[i], env);
			}
			free(env);
		}
		i++;
	}
	new_line = arr2D_to_str(split);
	return (new_line);
}
