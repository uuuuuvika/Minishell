/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:37:16 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 18:39:24 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error_and_code(char *arg, t_data *data)
{
	write_error("minishell: export: ");
	write_error(arg);
	write_error(": not a valid identifier\n");
	data->exit_code = 1;
}

int	varname_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}
