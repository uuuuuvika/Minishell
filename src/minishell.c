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

int main(int argc, char *argv[], char **envp)
{
	static t_data data;
	char *input;

	(void)argc;
	(void)argv;

	cpy_envs(&data, envp);
	while (1)
	{
		handle_ctrl();
		input = readline(YEL "Minishell > " RESET);
		if (!input || errno == EINVAL)
		{
			printf("you have pressed CTRL-D\n");
			break;
		}
		if (ft_strlen(input) > 0 && !is_str_space(input))
		{
			add_history(input);
			parse(input, &data);
			if ((data.num_of_children == 1 && is_builtin(data.commands)) || (data.num_of_children == 1 && is_dsqm(data.commands)) )
			{
				printf(YEL "Executing simple builtin/$? in main\n" RESET);
				int fin = dup(STDIN);
				int fout = dup(STDOUT);
				redirect_fd_dup(data.commands, &data);
				exec_cmd(&data, data.commands);
				dup2(fin, STDIN);
				dup2(fout, STDOUT);
			}
			else
			{
				printf(YEL "Fork\n" RESET);
				pipe_cmds(&data);
			}
			// printf("exit code in main is %d\n", data.exit_code);
		}
		free(input);
	}
	clear_history();
	return (0);
}
/// Commands not working
// env | grep $HOME stays open until ctrl-C