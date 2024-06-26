/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:45:12 by darotche          #+#    #+#             */
/*   Updated: 2024/06/26 19:43:58 by darotche         ###   ########.fr       */
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
	//	printf(MAG"handle_ctrl\n"RESET);////////////
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 1);// We need this line to clear the  input line when typing heredoc input but not hitting enter
		rl_on_new_line(); /// This line is for when we press ctrl+c before inputting anything
		//rl_redisplay();
		g_signal = 2;
		//printf(CYN "g_singal %d" RESET,g_signal);//////////////
	}
	else if (sig == SIGPIPE)
	{
		//printf(MAG"SIGPIPE\n"RESET);
		g_signal = 1;
	}
}
