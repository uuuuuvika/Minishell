/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dsqm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:31:46 by vshcherb          #+#    #+#             */
/*   Updated: 2024/07/06 22:12:34 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_substr(char *result, char *arg, int start, int len)
{
	char	*tmp;
	char	*new_result;

	tmp = ft_substr(arg, start, len);
	new_result = ft_strjoin(result, tmp);
	free(tmp);
	return (new_result);
}

char	*replace_dsqm(char *arg, t_data *data)
{
	int		i;
	int		j;
	char	*result;
	char	*tmp;

	i = 0;
	j = 0;
	result = ft_strdup("");
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			result = add_substr(result, arg, j, i - j);
			tmp = ft_itoa(data->exit_code);
			result = ft_strjoin(result, tmp);
			free(tmp);
			i += 2;
			j = i;
		}
		else
			i++;
	}
	result = add_substr(result, arg, j, i - j);
	return (result);
}

void	expand_dsqm(char **arg, t_data *data)
{
	char	*result;

	handle_sigint_exit_code(data);
	if (count_dsqm(arg) > 0)
	{
		result = replace_dsqm(*arg, data);
		free(*arg);
		*arg = result;
	}
}
