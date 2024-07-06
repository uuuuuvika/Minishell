/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:04:49 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 18:58:51 by vshcherb         ###   ########.fr       */
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
		line = expand_input_str(line, data);
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
		g_signal = 0;
		data->exit_code = 130;
		return (1);
	}
	if (g_signal == 2)
	{
		if (ft_strcmp(current->args[0], "cat") == 0)
			g_signal = 2;
		else
			g_signal = 0;
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

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	current->here_doc = fd;
	g_signal = 0;
	while (1)
	{
		line = readline("> ");
		if (handle_keypress_heredoc(line, current, data))
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			data->exit_code = 0;
			free(line);
			break ;
		}
		if (current->here_doc_exp)
			line = expand_input_str(line, data);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}
