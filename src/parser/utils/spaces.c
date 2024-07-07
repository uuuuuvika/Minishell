/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:05:05 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 19:06:20 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_missing_space(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] != ' ' && line[i + 1] != '\0'
				&& line[i + 1] != '>' && line[i + 1] != '<')
				count++;
			if (i > 0 && line[i - 1] != ' '
				&& line[i - 1] != '>' && line[i - 1] != '<')
				count++;
		}
		i++;
	}
	return (count);
}

char	*handle_missing_spaces(char *line)
{
	char	*new_line;

	if (cnt_missing_space(line) > 0)
	{
		new_line = add_space_to_redirect(line);
		free(line);
		return (new_line);
	}
	return (line);
}

char	*replace_tabs_with_spaces(char *line)
{
	char	*new_line;
	int		i;

	new_line = ft_strdup(line);
	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '\t')
			new_line[i] = ' ';
		i++;
	}
	return (new_line);
}
