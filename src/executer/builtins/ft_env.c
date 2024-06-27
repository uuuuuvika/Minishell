/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:35 by darotche          #+#    #+#             */
/*   Updated: 2024/06/26 19:01:42 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->envs == NULL)
		return ;
	while (data->envs[i] != NULL)
	{
		printf("%s\n", data->envs[i]);
		i++;
	}
	data->exit_code = 0;
}
