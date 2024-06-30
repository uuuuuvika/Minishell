/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:18:47 by darotche          #+#    #+#             */
/*   Updated: 2024/06/26 20:18:48 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] && !is_redirect(args[i]))
		i++;
	return (i);
}

void	pipe_assign(t_cmd *command)
{
	int		p[2];
	t_cmd	*current;
	t_cmd	*previous;

	current = command;
	previous = NULL;
	while (current)
	{
		if (previous)
		{
			pipe(p);
			previous->pipe_out = p[PIPE_WRITE];
			current->pipe_in = p[PIPE_READ];
		}
		previous = current;
		current = current->next;
	}
}


int cnt_missing_space(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == '>' || line[i] == '<')
        {
            if (line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != '>' && line[i + 1] != '<')
                count++;
            if (0 > 1 && line[i - 1] != ' ' && line[i - 1] != '>' && line[i - 1] != '<')
                count++;
        }
        i++;
    }
    return (count);
}

char	*replace_tabs_with_spaces(char *line)
{
    char	*new_line;
	int		i;

	new_line = ft_strdup(line);
	i = 0;
    while(new_line[i])
	{
        if (new_line[i] == '\t')
            new_line[i] = ' ';
		i++;
    }
	//free(line);
    return (new_line);
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