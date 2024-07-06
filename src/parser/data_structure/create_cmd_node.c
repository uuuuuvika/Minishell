/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:51:52 by vshcherb          #+#    #+#             */
/*   Updated: 2024/07/06 17:52:57 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd_node(char *cmd_str)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	new_node->args = ft_split(cmd_str, ' ');
	new_node->num_args = cnt_args(new_node->args);
	new_node->pipe_in = -1;
	new_node->pipe_out = -1;
	new_node->redirect_in = -1;
	new_node->redirect_out = -1;
	new_node->here_doc = 0;
	new_node->next = NULL;
	return (new_node);
}
