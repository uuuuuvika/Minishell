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

void sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
  	{
	//	printf(MAG"handle_ctrl\n"RESET);////////////
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 1);// We need this line to clear the  input line when typing heredoc input but not hitting enter
		rl_on_new_line(); /// This line is for when we press ctrl+c before inputting anything
		//rl_redisplay();
		g_signal = 2;
		//printf(CYN "g_singal %d" RESET,g_signal);//////////////
	}
	else if (sig == SIGPIPE)
	{
		printf(MAG"SIGPIPE\n"RESET);
		g_signal = 1;
	}
}


void read_heredoc(char *delimiter, t_cmd *current, t_data *data)
{
	char *line;
	int fd;
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	current->here_doc = fd; // probably can be replaced by data->cmn_here_doc
	g_signal = 0; // Important to reset signal
	while (1)
	{
		line = readline("> ");
		if (!line || errno == EINVAL)
		{
			printf(MAG "you have pressed CTRL-D\n" RESET);
			g_signal = 0; // need to reset g_signal, otherwise it will be 2 in the next iteration and the program will exit
			data->exit_code = 130;
			break;
		}
		if (g_signal == 2)
		{
        	printf(MAG"\nCTRL+C detected. Exiting heredoc...\n"RESET);
			g_signal = 0; // need to reset g_signal, otherwise it will be 2 in the next iteration and the program will exit
			free(line);
			data->exit_code = 130;//// !important for exit code
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
