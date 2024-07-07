/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 01:54:53 by vshcherb          #+#    #+#             */
/*   Updated: 2024/07/07 01:59:07 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_redirections(t_cmd *current, int *i)
{
	int	result;

	if (ft_strcmp(current->args[*i], ">") == 0)
	{
		result = process_redirection(current, i, O_WRONLY
				| O_CREAT | O_TRUNC, 1);
		if (result != 0) 
			return (result);
	}
	else if (ft_strcmp(current->args[*i], "<") == 0)
	{
		result = process_redirection(current, i, O_RDONLY, 0);
		if (result != 0)
			return (result);
	}
	else if (ft_strcmp(current->args[*i], ">>") == 0)
	{
		result = process_redirection(current, i, O_WRONLY 
				| O_CREAT | O_APPEND, 1);
		if (result != 0)
			return (result);
	}
	return (0);
}

int	redirect_assign(t_cmd *current, t_data *data)
{
	int	i;
	int	result;

	i = 0;
	while (current->args[i])
	{
		result = process_redirections(current, &i);
		if (result != -1)
		{
			if (result != 0)
				return (result);
		}
		else if (ft_strcmp(current->args[i], "<<") == 0)
		{
			read_heredoc(current->args[i + 1], current, data);
			i++;
		}
		i++;
	}
	return (0);
}
