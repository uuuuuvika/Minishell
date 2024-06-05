#include "minishell.h"

// to handle cat ', echo ' etc.
void read_heredoc_simple(char *delimiter, t_data *data)
{
	char *line;
	int fd;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	data->cmn_here_doc = fd;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
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

void read_heredoc(char *delimiter, t_cmd *current, t_data *data)
{
	char *line;
	int fd;
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	current->here_doc = fd; // probably can be replaced by data->cmn_here_doc

	//signal(SIGINT, handle_sigint);

	while (1)
	{
		line = readline("> ");
		if (!line || errno == EINVAL || g_signal == 2)
		{
			printf("you have pressed CTRL-D\n");
			g_signal = 0; // need to reset g_signal, otherwise it will be 2 in the next iteration and the program will exit
			data->exit_code = 130;
			//rl_replace_line("", 0);
			//clear_history();
			//free(line);
			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (current->here_doc_exp)
		{
			if (ft_strchr(line, '$')) // check if there are quotes
			{
				char *exp_line = split_expand_join(line, data);
				// free(line);
				line = exp_line;
				// free(exp_line);
			}
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}
