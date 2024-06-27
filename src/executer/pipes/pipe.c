/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:45:07 by darotche          #+#    #+#             */
/*   Updated: 2024/06/27 17:20:23 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_cmds(t_data *data)
{
    t_cmd	*current;
    pid_t	pid[data->num_of_children];
    int		i;

    i = 0;
    current = data->commands;
    while (current != NULL)
    {
		handle_ctrl_fork(data); // set signal handler for fork
        pid[i] = fork();
        if (pid[i] == -1)
            return EXIT_FAILURE;
        else if (pid[i] == 0)
        {
            fd_dup2(current);
            ultimate_fd_close(data);
            exec_cmd(data, current);
            exit(data->exit_code);
        }
        else
            fd_close(current);
        current = current->next;
        i++;
    }
    ultimate_wait(data, pid);
	handle_ctrl(); // reset signal handler
    return EXIT_SUCCESS;
}
