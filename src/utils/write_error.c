/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:54:28 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 01:25:53 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	write_error_arg(const char *arg, const char *msg)
{
	write(2, "minishell: ", 11);
	write(2, arg, ft_strlen(arg));
	write(2, msg, ft_strlen(msg));
}
