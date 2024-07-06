/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:44 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 17:36:08 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_nodes(t_data *data)
{
	t_cmd	*current;
	int		i;

	i = 0;
	printf("num_of_children: %d\n", data->num_of_children);
	current = data->commands;
	while (current)
	{
		printf("cmd: %s\n", current->args[0]);
		printf("num_args: %d\n", current->num_args);
		while (current->args[i])
		{
			printf("args[%d]: %s\n", i, current->args[i]);
			i++;
		}
		printf("pipe_in: %d\n", current->pipe_in);
		printf("pipe_out: %d\n", current->pipe_out);
		printf("here_doc: %d\n", current->here_doc);
		printf("redirect_in: %d\n", current->redirect_in);
		printf("redirect_out: %d\n", current->redirect_out);
		current = current->next;
	}
}
