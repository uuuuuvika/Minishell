/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:59:33 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 01:17:18 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dobarr(char **arr2D)
{
	int	i;

	i = 0;
	while (arr2D[i] != NULL)
		free(arr2D[i++]);
	free(arr2D);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (cmd == NULL)
		return ;
	current = cmd;
	while (current->next != NULL)
	{
		next = current->next;
		free_dobarr(current->args);
		current->args = NULL;
		current->num_args = 0;
		current->pipe_in = 0;
		current->pipe_out = 0;
		current->here_doc = 0;
		current->here_doc_exp = 0;
		current->redirect_in = 0;
		current->redirect_out = 0;
		free(current);
		current = next;
	}
	free_dobarr(current->args);
	free(current);
	current = NULL;
}

void	free_data(t_data *data)
{
	if (data->commands == NULL)
	{
		return ;
	}
	free_cmd(data->commands);
	data->commands = NULL;
	data->num_of_children = 0;
	free_dobarr(data->sub);
	free_dobarr(data->subb);
	data->sub = NULL;
	data->subb = NULL;
	data->cmn_here_doc = 0;
}