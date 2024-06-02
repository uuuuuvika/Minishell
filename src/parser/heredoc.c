#include "minishell.h"

// To fix:

// Minishell > << EOF
// delimiter: EOF
// > EOF
// make: *** [Makefile:19: m] Segmentation fault (core dumped)

char *split_expand_join(char *line, t_data *data)
{
	char *exp_line;
	char **splitted;
	int i;

	exp_line = ft_strdup("");
	splitted = ft_split(line, ' ');
	i = 0;

	// printf(BLU "line to expand: %s\n" RESET, line);
	// print_2D(splitted);
	// printf(BLU "num_args: %d\n" RESET, cnt_args(splitted));
	// print_2D(splitted);
	while (splitted[i])
	{
		// printf(BLU "Splitted[%d]: %s\n" RESET, i, splitted[i]);
		expand_arg(splitted, cnt_args(splitted), data);
		// printf(BLU "Expanded[%d]: %s\n" RESET, i, splitted[i]);
		//  if(ft_strchr(splitted[i], '$'))//Make it work for all expansions
		//  	splitted[i] = getenv(splitted[i] + 1);
		if (i > 0)
			exp_line = ft_strjoin(exp_line, " ");
		exp_line = ft_strjoin(exp_line, splitted[i]);
		i++;
	}
	// printf(GRN "expanded line: %s\n" RESET, exp_line);
	return (exp_line);
}

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
	// dup2(fd, STDIN);
	close(fd);
}

void read_heredoc(char *delimiter, t_cmd *current, t_data *data)
{
	//(void)current;
	char *line;
	int fd;
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	current->here_doc = fd; // probably can be replaced by data->cmn_here_doc 
	while (1)
	{
		line = readline("> ");
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
