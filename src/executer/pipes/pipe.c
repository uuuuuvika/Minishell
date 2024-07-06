/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:45:07 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 00:34:51 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input_dup(t_cmd *current)
{
	if (current->pipe_in != -1)
	{
		if (dup2(current->pipe_in, STDIN_FILENO) == -1)
			handle_error("dup2 error pipe_in");
	}
	else if (current->redirect_in != -1)
	{
		if (dup2(current->redirect_in, STDIN_FILENO) == -1)
			handle_error("dup2 error redirect_in");
	}
}

void	handle_output_dup(t_cmd *current)
{
	if (current->redirect_out != -1)
	{
		if (dup2(current->redirect_out, STDOUT_FILENO) == -1)
			handle_error("dup2 error redirect_out");
	}
	else if (current->pipe_out != -1)
	{
		if (dup2(current->pipe_out, STDOUT_FILENO) == -1)
			handle_error("dup2 error pipe_out");
	}
}

void	fd_dup2(t_cmd *current)
{
	handle_here_doc_dup(current);
	handle_input_dup(current);
	handle_output_dup(current);
}

void	do_pipe(t_data *data, t_cmd *current)
{
	fd_dup2(current);
	ultimate_fd_close(data);
	exec_cmd(data, current);
	exit(data->exit_code);
}

int	pipe_cmds(t_data *data)
{
	t_cmd	*current;
	pid_t	*pid;
	int		i;

	pid = malloc(sizeof(pid_t) * data->num_of_children);
	i = 0;
	current = data->commands;
	while (current != NULL)
	{
		handle_keypress_fork(data);
		pid[i] = fork();
		if (pid[i] == -1)
			return (EXIT_FAILURE);
		else if (pid[i] == 0)
			do_pipe(data, current);
		else
			fd_close(current);
		current = current->next;
		i++;
	}
	ultimate_wait(data, pid);
	free(pid);
	handle_keypress();
	return (EXIT_SUCCESS);
}
