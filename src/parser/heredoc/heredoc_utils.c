/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:01:28 by darotche          #+#    #+#             */
/*   Updated: 2024/07/02 13:26:20 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *split_expand_join(char *line, t_data *data)
{
	char *exp_line;
	char **splitted;
	int i;

	exp_line = ft_strdup("");
	splitted = ft_split(line, ' ');
	i = 0;
	while (splitted[i])
	{
		expand_arg(splitted, data);
		if (i > 0)
			exp_line = ft_strjoin(exp_line, " ");
		exp_line = ft_strjoin(exp_line, splitted[i]);
		i++;
	}
	return (exp_line);
}

int heredoc_preprocess(t_cmd *new_node, t_data *data)
{
	int i;

	i = 0;
	while (new_node->args[i])
	{
		if (ft_strcmp(new_node->args[i], "<<") == 0)
		{
			if (new_node->args[i + 1] == NULL)
			{
				// free_arr2D(new_node->args);
				// free(new_node);
				data->exit_code = 2;
				write_error("syntax error near unexpected token `newline'\n");
				return (1);
			}
			else if (new_node->args[i + 1][0] == '\'' || new_node->args[i + 1][0] == '\"')
				new_node->here_doc_exp = 0;
			else
				new_node->here_doc_exp = 1;
		}
		i++;
	}
	return (0);
}
