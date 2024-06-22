/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:27 by darotche          #+#    #+#             */
/*   Updated: 2024/06/21 02:45:03 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_data *data, t_cmd *cmd, int i)
{
    (void) data;
   // int i;

    //i = 1;
    i++;
    
    while (cmd->args && ft_strcmp(cmd->args[i], "-n") == 0) 
        i++;
    while (cmd->args[i])
    {
        if (!cmd->args[i])
            return ;
        printf("%s", cmd->args[i]);
        i++;
        if (cmd->args[i] != NULL)
            printf(" ");
    }
    if (ft_strcmp(cmd->args[1], "-n") != 0)
		printf("\n");
	data->exit_code = 0;
}