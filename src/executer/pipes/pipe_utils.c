/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vika <vika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:44:59 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 12:47:33 by vika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_close(t_cmd *current)
{
	if (current->pipe_in != -1)
		close(current->pipe_in);
	if (current->pipe_out != -1)
		close(current->pipe_out);
	if (current->redirect_in != -1)
		close(current->redirect_in);
	if (current->redirect_out != -1)
		close(current->redirect_out);
	if (current->here_doc != 0)
		close(current->here_doc);
}

void	ultimate_fd_close(t_data *data)
{
	t_cmd	*current;

	current = data->commands;
	while (current != NULL)
	{
		fd_close(current);
		current = current->next;
	}
}

void	ultimate_wait(t_data *data, pid_t *pid)
{
	int	i;
	int	exit_code;

	i = 0;
	while (i < data->num_of_children)
	{
		if (waitpid(pid[i], &exit_code, 0) == -1)
			write_error(ERR_WAITPID);
		if (WIFEXITED(exit_code))
			data->exit_code = WEXITSTATUS(exit_code);
		i++;
	}
}

void	handle_here_doc_dup(t_cmd *current)
{
	int	here_doc_fd;

	if (current->here_doc != 0)
	{
		here_doc_fd = open("here_doc", O_RDONLY, 777);
		if (dup2(here_doc_fd, STDIN_FILENO) == -1)
			write_error(ERR_DUP2_HER_DOC);
		close(here_doc_fd);
	}
}
