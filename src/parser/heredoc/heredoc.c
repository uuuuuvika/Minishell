/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:04:49 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 17:32:56 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc_simple(char *delimiter, t_data *data)
{
	char	*line;
	int		fd;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	data->cmn_here_doc = fd;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$'))
		{
			free(line);
			line = split_expand_join(line, data);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

int	handle_keypress_heredoc(char *line, t_cmd *current, t_data *data)
{
	if (!line || errno == EINVAL)
	{
        //printf(MAG "you have pressed CTRL-D\n" RESET);
		g_signal = 0;
		data->exit_code = 130;
		return (1);
	}
	if (g_signal == 2)
	{
        //printf(MAG "\nCTRL+C detected. Exiting heredoc...\n" RESET);
		if (ft_strcmp(current->args[0], "cat") == 0)
			g_signal = 2; // Reset g_signal
		else
			g_signal = 0; // Reset g_signal
		free(line);
		data->exit_code = 130;
		return (1); 
	}
	return (0);
}

void	read_heredoc(char *delimiter, t_cmd *current, t_data *data)
{
	char	*line;
	int		fd;
	//char *exp_line;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	current->here_doc = fd;
	
	g_signal = 0; // Important to reset signal
	while (1)
	{
		line = readline("> ");
		if (handle_keypress_heredoc(line, current, data))
		{
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			data->exit_code = 0;
			free(line);
			break ;
		}
		if (current->here_doc_exp)
		{
			//if (ft_strchr(line, '$')) // check if there are quotes
			//{
				//exp_line = split_expand_join(line, data);
				// free(line);
				line = expand_input_str(line, data);
				// free(exp_line);
			//}
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	//close(fd);
}
