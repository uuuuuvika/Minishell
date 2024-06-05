#include "minishell.h"

// To try:

// c4a9c8% cat << 'EOF'
// heredoc> $USER
// heredoc> EOF
// $USER

// c4a9c8% cat << "EOF"
// heredoc> $USER
// heredoc> EOF
// $USER

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

	printf(BLU "line to expand: %s\n" RESET, line);
	print_2D(splitted);
	printf(BLU "num_args: %d\n" RESET, cnt_args(splitted));
	print_2D(splitted);
	while (splitted[i])
	{
		printf(BLU"Splitted[%d]: %s\n" RESET, i, splitted[i]);
		expand_arg(splitted, cnt_args(splitted), data);
		printf(BLU"Expanded[%d]: %s\n"RESET, i, splitted[i]);
		// if(ft_strchr(splitted[i], '$'))//Make it work for all expansions
		// 	splitted[i] = getenv(splitted[i] + 1);
		if(i > 0)
			exp_line = ft_strjoin(exp_line, " ");
		exp_line = ft_strjoin(exp_line, splitted[i]);
		i++;
	}
	printf(GRN "expanded line: %s\n" RESET, exp_line);
	return (exp_line);
}


void read_heredoc(char *delimiter, t_cmd *current, t_data *data)
{
	//(void)current;
	char *line;
	int fd;
	//char *joined_line = ft_strdup("");
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	current->here_doc = fd;
	//dup2(fd, STDOUT);
	printf(BLU"current %s\n" RESET,current->args[0]);
		// fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("delimiter: %s\n", delimiter);
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
        	printf("\nCTRL+C detected. Exiting readline...\n");
			free(line);
			//rl_replace_line("", 1);
			//data->commands = NULL;
			g_signal = 0;
            break; // Exit the loop when CTRL+C is detected
        }
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (delimiter[0] != '\'' || delimiter[0] != '\"')////// not nice
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

// else
// {
// 	ft_strjoin(line, joined_line);
// 	printf(RED"LINE: %s\n"RESET , joined_line);
// 	line = joined_line;
// 	printf(RED"LINE: %s\n"RESET , line);
// 	//free(joined_line);
// }


// char *expand_var(char *args, t_data *data)
// {
// 	int i = 0;
// 	if (args[i] == '$' && ft_strchr(args, '\'') == 0)
// 	{
// 		char *env_name = ft_strdup(args + 1);
// 		printf(BLU"env_name: %s\n" RESET, env_name);
// 		if (ft_getenv(env_name, data->envs) != NULL)
// 		{
// 			printf(GRN"Valid env: %s\n" RESET, env_name);
// 			free(args);
// 			args = ft_strdup(ft_getenv(env_name, data->envs));
// 			free(env_name);
// 			return (args);
// 		}
// 		else if (ft_strcmp(args, "$?") == 0) /// Replace for exit code since we can do 'echo $?'
// 		{
// 			// printf(YEL"cmd is $?\n" RESET);// pass ? as a cmd and later in exec_cmd replace it for data->exit code
// 			// args[i] = ft_strdup("$?");
// 			args = ft_itoa(data->exit_code);
// 			free(env_name);
// 			return (args);
// 		}
// 		else
// 		{
// 			printf(RED"Not valid env: %s \n" RESET, env_name);
// 			free(env_name);
// 			args[i] = '\0';
// 		}
// 	}
// 	return(args);
// }


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
