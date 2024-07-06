/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:51:41 by vshcherb          #+#    #+#             */
/*   Updated: 2024/07/06 17:52:44 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_node)
{
	t_cmd	*current;

	current = NULL;
	if (*cmd_list == NULL)
		*cmd_list = new_node;
	else
	{
		current = *cmd_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
