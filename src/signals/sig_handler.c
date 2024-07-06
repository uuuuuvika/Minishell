/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:45:12 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 18:13:48 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	handle_keypress(void)
{
	rl_bind_key('\t', rl_insert);
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

void	handle_keypress_fork(t_data *data)
{
	if (signal(SIGINT, sig_handler_fork))
		data->exit_code = 130;
	signal(SIGQUIT, SIG_IGN);
}

void handle_sigint_exit_code(t_data *data)
{
    if (g_signal == 2)
    {
        data->exit_code = 130;
        g_signal = 0;
    }
}
