/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:34:57 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 19:01:42 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dobarr(char **args)
{
	int	j;

	j = 0;
	while (args[j])
	{
		printf(BLU "args[%d]: %s\n" RESET, j, args[j]);
		j++;
	}
}
