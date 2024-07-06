/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:47:24 by vshcherb          #+#    #+#             */
/*   Updated: 2024/07/07 00:47:27 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redirects(t_cmd *new_node, t_data *data, char **future_children)
{
    int j;

    j = redirect_assign(new_node, data);
    if (j != 0)
    {
        free_arr2D(new_node->args);
        free(new_node);
        free_arr2D(future_children);
        free_arr2D(data->sub);
        free_arr2D(data->subb);
        data->exit_code = j;
        return (1);
    }
    return (0);
}
