/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space_to_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 02:04:18 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 02:24:54 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_space(char *line, char *new_line, int *i, int *j)
{
	if (line[*i + 1] == '>' || line[*i + 1] == '<')
	{
		new_line[(*j)++] = ' ';
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = ' ';
	}
	else if (i != 0 && line[(*i) - 1] != ' '
		&& line[(*i) - 1] != '>' && line[(*i) - 1] != '<')
	{
		new_line[(*j)++] = ' ';
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = ' ';
	}
	else if (line[(*i) + 1] != '\0' && line[(*i) + 1] != ' '
		&& line[(*i) + 1] != '>' && line[(*i) + 1] != '<')
	{
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = ' ';
	}
}

char	*add_space_to_redirect(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = malloc(sizeof(char) * (ft_strlen(line) * 2 + 1));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			insert_space(line, new_line, &i, &j);
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}
