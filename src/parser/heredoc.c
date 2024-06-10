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
	//char *joined_line = ft_strdup("");
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	current->here_doc = fd;
	printf(BLU"current->here_doc: %d\n" RESET, current->here_doc);
	//dup2(fd, STDOUT);
	printf(BLU"current %s\n" RESET,current->args[0]);
		// fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf(BLU"delimiter: %s\n"MAG, delimiter);
	// int orig_rl_catch_signals = rl_catch_signals;
    // rl_catch_signals = 0;    
	while (1)
	{
		g_signal = 0;
		printf(MAG"g_signal: %d\n"RESET, g_signal);
		line = readline("> ");
		if (!line || errno == EINVAL) {
			printf("you have pressed CTRL-D\n");
			data->commands = NULL;
			break;
        }
		if (g_signal == 2)
		{
        	printf(MAG"\nCTRL+C detected. Exiting readline...\n"RESET);
			free(line);
			//rl_replace_line("", 1);
			//data->commands = NULL;
			data->exit_code = 130;//// !important for exit code
			g_signal = 0;
            break; // Exit the loop when CTRL+C is detected
        }
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (current->here_doc_exp)
		{
			if (ft_strchr(line, '$'))
			{
				char *exp_line = split_expand_join(line, data);
				free(line);
				line = exp_line;
				printf(	RED"LINE: %s\n"RESET , exp_line);
				//free(exp_line);
			}
		}
		printf(RED"LINE: %s\n"RESET , line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	//rl_catch_signals = orig_rl_catch_signals;
	close(fd);
}
