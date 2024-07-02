/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:59:33 by darotche          #+#    #+#             */
/*   Updated: 2024/07/02 15:12:03 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr2D(char **arr2D)
{
	int	i;

	i = 0;
	while (arr2D[i] != NULL)
		free(arr2D[i++]);
	free(arr2D);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	while (current != NULL)
	{
		next = current->next;
		free_arr2D(current->args);
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
	free(current);
}

void	free_data(t_data *data)
{
	if (data->commands == NULL)
	{
		return ;
	}
	free_cmd_list(data->commands);
	data->num_of_children = 0;
	free_arr2D(data->sub);
	free_arr2D(data->subb);
	data->sub = NULL;
	data->subb = NULL;
	data->cmn_here_doc = 0;
}
