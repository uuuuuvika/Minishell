/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:45:12 by darotche          #+#    #+#             */
/*   Updated: 2024/06/27 17:54:29 by darotche         ###   ########.fr       */
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
		// printf(MAG"handle_ctrl\n"RESET);////////////
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 1);
		rl_on_new_line(); /// This line is for when we press ctrl+c before inputting anything
		g_signal = 2;
		//printf(CYN "g_singal %d" RESET,g_signal);//////////////
	}
	else if (sig == SIGPIPE)
	{
		//printf(MAG"SIGPIPE\n"RESET);
		g_signal = 1;
	}
}

void	sig_handler_fork(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_signal = 0; // need to reset g_signal, otherwise it will be 2 in the next iteration and the program will exit in heredoc
		// printf(MAG"handle_ctrl_fork\n"RESET);
		// printf(CYN "g_singal %d" RESET,g_signal);
	}
}

void	handle_ctrl_fork(t_data *data)
{
	if (signal(SIGINT, sig_handler_fork))
		data->exit_code = 130;// !important
	signal(SIGQUIT, SIG_IGN);
}
