/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:01:28 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 19:00:34 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_preprocess(t_cmd *new_node, t_data *data)
{
	int	i;

	i = 0;
	while (new_node->args[i])
	{
		if (ft_strcmp(new_node->args[i], "<<") == 0)
		{
			if (new_node->args[i + 1] == NULL)
			{
				data->exit_code = 2;
				write_error(ERR_SYNTAX);
				return (1);
			}
			else if (new_node->args[i + 1][0] == '\'' 
			|| new_node->args[i + 1][0] == '\"')
				new_node->here_doc_exp = 0;
			else
				new_node->here_doc_exp = 1;
		}
		i++;
	}
	return (0);
}
