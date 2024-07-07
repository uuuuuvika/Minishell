/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dobarr_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:21:04 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 02:09:44 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dobarr_to_str(char **args)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (args[i])
	{
		if (i > 0)
			str = ft_strjoin(str, " ");
		str = ft_strjoin(str, args[i]);
		i++;
	}
	free_dobarr(args);
	return (str);
}
