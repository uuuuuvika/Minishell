#include "minishell.h"
#include <termios.h>

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

	rl_bind_key('\t', rl_insert);

	handle_ctrl();
	cpy_envs(&data, envp);
	printf("\n");
	// printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf(MAG "\t __  __  __  _  _  __  ___  _  _  ___  __    __      \n");
	printf("\t(  \\/  )(  )( \\( )(  )/ __)( )( )(  _)(  )  (  )     \n");
	printf("\t )    (  )(  )  (  )( \\__ \\ )__(  ) _) )(__  )(__    \n");
	printf("\t(_/\\/\\_)(__)(_)\\_)(__)(___/(_)(_)(___)(____)(____)    \n");
	printf("                                                           \n" RESET);
	printf(CYN " \t \t\tby Vika & Dai, Berlin Summer 2024     \n" RESET);
	printf("                                                            \n");
	// printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	while (1)
	{
		input = readline(YEL "Minishell > " RESET);
		if (!input || errno == EINVAL || errno == EIO || errno == EINTR)
		{
			free(input);
			free_data(&data);
			break;
		}

		if (ft_strlen(input) > 0 && !is_str_space(input))
		{
			add_history(input);
			if (parse(input, &data) != 0)
			{
				free(input);
				continue;
			}

			int i = 0;
			while (data.commands && ft_strcmp(data.commands->args[i], "") == 0 && data.commands->args[i + 1] != NULL)
				i++;

			if ((data.num_of_children == 1 && is_builtin(data.commands->args[i])) || (data.num_of_children == 1 && is_dsqm(data.commands)))
			{
				// printf(YEL "Executing simple builtin/$? in main\n" RESET);
				int fin = dup(STDIN);
				int fout = dup(STDOUT);
				redirect_fd_dup(data.commands, &data);
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