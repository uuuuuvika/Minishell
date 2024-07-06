/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:18:47 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 19:04:48 by darotche         ###   ########.fr       */
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

void	args_realloc(t_cmd *new_node)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (new_node->num_args + 1));
	i = 0;
	while (i < new_node->num_args)
	{
		temp[i] = ft_strdup(new_node->args[i]);
		i++;
	}
	temp[i] = NULL;
	free_arr2D(new_node->args);
	new_node->args = temp;
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
