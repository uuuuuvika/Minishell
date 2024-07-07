/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 01:32:12 by vshcherb          #+#    #+#             */
/*   Updated: 2024/07/07 02:00:38 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(const char *f, int flags, t_cmd *current, int is_out)
{
	int	fd;

	fd = open(f, flags, 0644);
	if (fd == -1)
	{
		if (f)
		{
			write_error_arg(f, ERR_NO_FILE);
			return (1);
		}
		write_error(ERR_SYNTAX);
		return (2);
	}
	if (is_out)
		current->redirect_out = fd;
	else
		current->redirect_in = fd;
	return (0);
}
