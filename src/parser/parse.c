/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:57:05 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 02:37:24 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_quotes(char *input, t_data *data)
{
	if (ft_strcmp(input, "\'\'") == 0 || ft_strcmp(input, "\"\"") == 0)
	{
		printf("minishell: : command not found\n");
		data->exit_code = 127;
		return (1);
	}
	if (ft_strcmp(input, "\' \'") == 0 || ft_strcmp(input, "\" \"") == 0)
	{
		printf("minishell:  : command not found\n");
		data->exit_code = 127;
		return (1);
	}
	return (0);
}

int	create_child_nodes(t_data *data, char *expanded_line)
{
	char	**future_children;
	t_cmd	*new_node;
	int		nch;

	future_children = ft_split(expanded_line, '|');
	free(expanded_line);
	new_node = NULL;
	nch = 0;
	while (future_children[nch])
	{
		new_node = create_cmd_node(future_children[nch]);
		if (heredoc_preprocess(new_node, data))
			return (1);
		return_dub_quotes(new_node->args, data);
		expand_arg(new_node->args, data);
		return_sin_quotes(new_node->args, data);
		if (handle_redirects(new_node, data, future_children))
			return (1);
		args_realloc(new_node);
		add_cmd_to_list(&(data->commands), new_node);
		nch++;
	}
	data->num_of_children = nch;
	free_dobarr(future_children);
	return (0);
}

int	parse(char *input, t_data *data)
{
	char	*expanded_line;

	if (empty_quotes(input, data))
		return (1);
	expanded_line = refine_input(input, data);
	if (!expanded_line)
		return (1);
	if (create_child_nodes(data, expanded_line))
		return (1);
	pipe_assign(data->commands);
	return (0);
}
