/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:08:28 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 18:01:40 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_str_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_dsqm(t_cmd *cmd)
{
	return (ft_strcmp(cmd->args[0], "$?") == 0);
}

void	print_banner(void)
{
	printf("\n");
	printf(YEL"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("*   __  __  __  _  _  __  ___  _  _  ___  __    __      *\n");
	printf("*  (  \\/  )(  )( \\( )(  )/ __)( )( )(  _)(  )  (  )     *\n");
	printf("*   )    (  )(  )  (  )( \\__ \\ )__(  ) _) )(__  )(__    *\n");
	printf("*  (_/\\/\\_)(__)(_)\\_)(__)(___/(_)(_)(___)(____)(____)   *\n");
	printf("*                                                       *\n");
	printf("*                  by Vika & Dai, Berlin Summer 2024    *\n");
	printf("*                                                       *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n"RESET);
}
