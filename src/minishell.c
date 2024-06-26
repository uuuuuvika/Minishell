#include "minishell.h"

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int is_str_space(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int is_dsqm(t_cmd *cmd)
{
	return (ft_strcmp(cmd->args[0], "$?") == 0);
}

// int	is_dsqm(t_cmd *cmd)
// {
// 	// if (ft_strcmp(cmd->args[0], "$?") != 0 || ft_strncmp(cmd->args[0], "$", 1) != 0)
// 	// 	return (1);
// 	// return (0);
// 	return (ft_strncmp(cmd->args[0], "$?", 1) == 0 || ft_strcmp(cmd->args[0], "") == 0);
// }

int main(int argc, char *argv[], char **envp)
{
	static t_data data;
	char *input;

	(void)argc;
	(void)argv;

	handle_ctrl();
	cpy_envs(&data, envp);
	while (1)
	{
		input = readline(YEL "Minishell > " RESET);
		if (!input || errno == EINVAL)
		{
			free(input);
			// printf(MAG "you have pressed CTRL-D\n" RESET);
			break ;
		}
		if (ft_strlen(input) > 0 && !is_str_space(input))
		{
			add_history(input);
			if (parse(input, &data))
			{
				free(input);
				//printf("vghjhm mError: syntax error near unexpected token `newline'\n");
				continue;
			}
			//print_2D(data.commands->args);
			// printf("%d\n", is_dsqm(data.commands));

			int i = 0;
			while (data.commands && ft_strcmp(data.commands->args[i], "") == 0 && data.commands->args[i + 1] != NULL)
				i++;

			if ((data.num_of_children == 1 && is_builtin(data.commands->args[i])) || (data.num_of_children == 1 && is_dsqm(data.commands)))
			{

				//printf(YEL "Executing simple builtin/$? in main\n" RESET);
				//printf(RED "cmd is: %s\n" RESET, data.commands->args[i]);
				int fin = dup(STDIN);
				int fout = dup(STDOUT);
				redirect_fd_dup(data.commands, &data);
				// print_2D(data.commands->args);
				exec_cmd(&data, data.commands);
				dup2(fin, STDIN);
				dup2(fout, STDOUT);
			}
			else if (ft_strncmp(input, "<<", 2) != 0 && data.commands) // << E | wc maybe??
			{
				// printf(RED "in pipes cmd is: %s\n" RESET, data.commands->args[i]);
				// printf(YEL "Pipe" RESET);
				// printf(RESET "\n" RESET);
				pipe_cmds(&data);
			}
		}
		free_data(&data);
		free(input);
	}
	clear_history();
	return (0);
}