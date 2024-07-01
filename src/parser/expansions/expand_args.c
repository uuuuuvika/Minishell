/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:44:59 by darotche          #+#    #+#             */
/*   Updated: 2024/06/27 14:41:05 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env_variable(char **arg, t_data *data)
{
	char	*env_key;
	char	*env_value;

	env_key = ft_strdup(*arg + 1);
	env_value = ft_getenv(env_key, data->envs);
	if (env_value != NULL)
		replace_for_expansion(arg, env_value);
	else
		(*arg)[0] = '\0';
	free(env_key);
	free(env_value);
}

void expand_multiple_args(char **split, t_data *data)
{
	int j;

	j = 0;
	while (split[j])
	{
		if (split[j][0] == '$' && split[j][1] == '?')
		{
			expand_dsqm(&split[j], data);
			//return;
		}
		else if (split[j][0] == '$')
			expand_env_variable(&split[j], data);
		j++;
	}
}

void expand_single_arg(char **arg, t_data *data)
{
	if ((*arg)[0] == '$' && (*arg)[1] != '?')
		expand_env_variable(arg, data);
	else
		expand_dsqm(arg, data);
}

void	expand_arg(char **args, t_data *data)
{
	int		i;
	char	**split;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		if (!is_all_dollars(args[i]))
		{
			if (is_multi_words(args[i]))
			{
				split = ft_split(args[i], ' ');
				expand_multiple_args(split, data);
				tmp = arr2D_to_str(split);
				free(args[i]);
				args[i] = ft_strdup(tmp);
				free(tmp);
			}
			else
				expand_single_arg(&args[i], data);
		}
		i++;
	}
}
