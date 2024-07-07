/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:08 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 01:50:01 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnumeric(const char *str)
{
	if (*str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1); 
}

void	exit_error_and_code(char *arg, t_data *data)
{
	write_error("minishell: exit: ");
	write_error(arg);
	write_error(": numeric argument required\n");
	data->exit_code = 2;
}

void	ft_exit(t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (data->commands->num_args > 2)
	{
		write_error("minishell: exit: too many arguments\n");
		data->exit_code = 1;
	}
	else if (data->commands->num_args == 2)
	{
		if (!ft_isnumeric(data->commands->args[1]))
			exit_error_and_code(data->commands->args[1], data);
		else
		{
			exit_code = (unsigned char)ft_atoi(data->commands->args[1]);
			data->exit_code = exit_code;
		}
	}
	else
		data->exit_code = 0;
	free_dobarr(data->envs);
	free_data(data);
	clear_history();
	exit(data->exit_code);
}
