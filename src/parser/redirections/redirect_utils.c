/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 01:54:44 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 01:59:09 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(char *str)
{
	return (ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<<") == 0);
}

int	handle_redir(const char *f, int flags, t_cmd *current, int is_out)
{
	int	result;

	result = open_file(f, flags, current, is_out);
	return (result);
}

int	process_redirection(t_cmd *current, int *index, int flags, int is_out)
{
	int	result;

	result = handle_redir(current->args[*index + 1], flags, current, is_out);
	if (result != 0)
		return (result);
	(*index)++;
	return (0);
}
