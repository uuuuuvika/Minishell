/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:45:07 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 18:56:14 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
