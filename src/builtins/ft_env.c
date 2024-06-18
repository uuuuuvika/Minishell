/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:35 by darotche          #+#    #+#             */
/*   Updated: 2024/06/18 13:40:37 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(t_data *data)
{
    int i;

    i = 0;
    if (data->envs == NULL)
    {
       // printf(RED "envp is null\n" RESET);
        return;
    }
    while (data->envs[i] != NULL)
    { 
        printf("%s\n", data->envs[i]);
        i++;
    }
	data->exit_code = 0;
}
