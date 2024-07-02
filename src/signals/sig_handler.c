/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:45:12 by darotche          #+#    #+#             */
/*   Updated: 2024/07/02 15:14:23 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	handle_ctrl(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		g_signal = 2;
	}
	else if (sig == SIGPIPE)
		g_signal = 1;
}

void	sig_handler_fork(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_signal = 0;
	}
}

void	handle_ctrl_fork(t_data *data)
{
	if (signal(SIGINT, sig_handler_fork))
		data->exit_code = 130;
	signal(SIGQUIT, SIG_IGN);
}
