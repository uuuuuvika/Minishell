/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:47:24 by vshcherb          #+#    #+#             */
/*   Updated: 2024/07/07 01:39:07 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirects(t_cmd *new_node, t_data *data, char **future_children)
{
	int	j;

    j = redirect_assign(new_node, data);
    if (j != 0)
    {
        free_dobarr(new_node->args);
        free(new_node);
        free_dobarr(future_children);
        free_dobarr(data->sub);
        free_dobarr(data->subb);
        data->exit_code = j;
        return (1);
    }
    return (0);
}
