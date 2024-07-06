/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:18:12 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 18:14:12 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ctrl_d(char *input, t_data *data)
{
	if (!input || errno == EINVAL || errno == EIO)
	{
		free(input);
		free_data(data);
		return (1);
	}
	return (0);
}

void simplecmd_or_pipe(t_data *data)
{
	int i;
	int fin;
	int fout;

	i = 0;
	while (data->commands && ft_strcmp(data->commands->args[i], "") == 0 && data->commands->args[i + 1] != NULL)
	{
		i++;
	}
	if ((data->num_of_children == 1 && is_builtin(data->commands->args[i])) || (data->num_of_children == 1 && is_dsqm(data->commands)))
	{
		// printf(YEL "Executing simple builtin/$? in main\n" RESET);
		fin = dup(STDIN);
		fout = dup(STDOUT);
		redirect_fd_dup(data->commands, data);
		exec_cmd(data, data->commands);
		dup2(fin, STDIN);
		dup2(fout, STDOUT);
	}
	else
		// printf(YEL "Pipe\n" RESET);
		pipe_cmds(data);
}

void free_main(t_data *data, char *input)
{
	free_data(data);
	free(input);
}

int	main(void)
{
	static t_data	data;
	extern char		**environ;
	char			*input;

	handle_keypress();
	cpy_envs(&data, environ);
	while (1)
	{
		input = readline(YEL "Minishell > " RESET);
		if (ctrl_d(input, &data))
			break;
		if (ft_strlen(input) > 0 && !is_str_space(input))
		{
			add_history(input);
			if (parse(input, &data) != 0)
			{
				free(input);
				continue;
			}
			simplecmd_or_pipe(&data);
		}
		free_main(&data, input);
	}
	clear_history();
	return (0);
}
