/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:10:23 by darotche          #+#    #+#             */
/*   Updated: 2024/07/02 14:49:21 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envs(t_data *data)
{
	int	i;

	i = 0;
	while (data->envs[i] != NULL)
	{
		printf(GRN "%s\n" RESET, data->envs[i]);
		i++;
	}
}
