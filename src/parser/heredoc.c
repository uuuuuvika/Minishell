#include "minishell.h"

// To try:
// c4a9c8% cat <<EOF
// heredoc> $USER
// heredoc> EOF
// darotche

// c4a9c8% cat << 'EOF'
// heredoc> $USER
// heredoc> EOF
// $USER

// c4a9c8% cat << "EOF"
// heredoc> $USER
// heredoc> EOF
// $USER

char *split_expand_join(char *line)
{
	int i = 0;
	char *exp_line = ft_strdup("");
	char **splitted = ft_split(line, ' ');

	printf(RED "line to expand: %s\n" RESET, line);
	print_2D(splitted);
	printf("num_args: %d\n", cnt_args(splitted));
	while(splitted[i])
	{
		if(ft_strchr(splitted[i], '$'))
			splitted[i] = getenv(splitted[i] + 1);
		//exp_line = ft_strjoin(line, splitted[i]);
		if(i > 0)
			exp_line = ft_strjoin(exp_line, " ");
		exp_line = ft_strjoin(exp_line, splitted[i]);
		i++;
	}
	printf(GRN "expanded line: %s\n" RESET, exp_line);
	return (exp_line);
}


void read_heredoc(char *delimiter, t_cmd *current)
{
	(void)current;
	char *line;
	int fd;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	current->here_doc = fd;
	//dup2(fd, STDOUT);

	// fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
			char *exp_line = split_expand_join(line);
			free(line);
			line = exp_line;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

// char *get_delimiter(char *line)
// {
// 	int i;
// 	int j;
// 	char *delimiter;

// 	i = 2;
// 	// while (line[i] != '<' && line[i + 1] != '<')
// 	// 	i++;
// 	j = i;
// 	while (line[j])
// 		j++;
// 	delimiter = ft_substr(line, i, j - i);
// 	printf("delimiter len: %zu\n", ft_strlen(delimiter));
// 	printf("delimiter: %s\n", delimiter);
// 	return (delimiter);
// }

// int is_heredoc(char **args)
// {
// 	int i;

// 	i = 0;
// 	printf("args[0]: %s\n", args[0]);
// 	while (args[i])
// 	{
// 		if ((args[i][0] == '<') && (args[i][1] == '<'))
// 		{
// 			printf(YEL "'<<' found: %s\n" RESET, args[i]);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void remove_arg(char **args, int i)
// {
// 	int j;

// 	j = i;
// 	free(args[j]);
// 	while (args[j])
// 	{
// 		args[j] = args[j + 1];
// 		j++;
// 	}
// }

// char *heredoc(char **args, t_data *data)
// {
// 	(void)data;
// 	char *delimiter;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	if (is_heredoc(args) == 0)
// 		return (0);
// 	while (args[i])
// 	{
// 		if (args[i][0] == '<' && args[i][1] == '<')
// 		{
// 			delimiter = get_delimiter(args[i]);
// 			remove_arg(args, i);
// 			break;
// 		}
// 		i++;
// 	}

// 	return (0);
// }
