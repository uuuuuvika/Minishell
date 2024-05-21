#include "minishell.h"
// void    redirect_fd_dup_back(t_cmd *current)
// {
// }

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
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			parse(input, &data);
			if ((data.num_of_children == 1 && is_builtin(data.commands)) || (data.num_of_children == 1 && is_expansion(data.commands->args)))
			{
				int fin = dup(STDIN);
				int fout = dup(STDOUT);
				//printf(YEL "Executing simple builtin in main\n" RESET);
				redirect_fd_dup(data.commands);
				exec_cmd(&data, data.commands);
				dup2(fin, STDIN);
				dup2(fout, STDOUT);
			}
			else
			{
				//printf(YEL "Fork\n" RESET);
				pipe_cmds(&data);
			}
			// if(data.exit_code == 127)
			// 	printf("command not found\n");
			// printf("exit code in main is %d\n", data.exit_code);
			//  printf("g_signal in main is %d\n", g_signal);
		}
		free(input);
	}
	return (0);
}

/// Commands not working
// env | grep $HOME stays open until ctrl-C