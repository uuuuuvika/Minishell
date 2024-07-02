/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:45:12 by darotche          #+#    #+#             */
/*   Updated: 2024/06/29 21:41:08 by vshcherb         ###   ########.fr       */
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
		// printf(MAG"handle_keypress\n"RESET);////////////
		ioctl(0, TIOCSTI, "\n");
		//rl_replace_line("", 1);
		rl_on_new_line(); /// This line is for when we press ctrl+c before inputting anything
		g_signal = 2;
		//printf(CYN "g_singal %d" RESET,g_signal);//////////////
	}
	else if (sig == SIGPIPE)
	{
		g_signal = 1;
	}
}

void	sig_handler_fork(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_signal = 0; // need to reset g_signal, otherwise it will be 2 in the next iteration and the program will exit in heredoc
		// printf(MAG"handle_keypress_fork\n"RESET);
		// printf(CYN "g_singal %d" RESET,g_signal);
	}
}

void	handle_keypress_fork(t_data *data)
{
	if (signal(SIGINT, sig_handler_fork))
		data->exit_code = 130;// !important
	signal(SIGQUIT, SIG_IGN);
}
