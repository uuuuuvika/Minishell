/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:24:01 by vshcherb          #+#    #+#             */
/*   Updated: 2024/07/07 00:54:06 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_fd_dup(t_cmd *current, t_data *data)
{
	if (current->redirect_in != -1)
	{
		if (dup2(current->redirect_in, STDIN) == -1)
			write_error(ERR_DUP2_RED_IN);
		close(current->redirect_in);
	}
	if (current->redirect_out != -1)
	{
		if (dup2(current->redirect_out, STDOUT) == -1)
			write_error(ERR_DUP2_RED_OUT);
		close(current->redirect_out);
	}
	if (data->cmn_here_doc != 0)
	{
		if (dup2(data->cmn_here_doc, STDOUT) == -1)
			write_error(ERR_DUP2_HER_DOC);
		close(data->cmn_here_doc);
	}
}
