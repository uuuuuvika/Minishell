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
