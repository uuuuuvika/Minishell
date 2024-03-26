#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	static t_data data;

	(void)argc;
	(void)argv;
	data.envp = envp;
	while (1)
	{
		
		char *input = readline(YEL "Minishell > " RESET);
		parse(input, &data);
		pipe_it(&data);
		// exec_cmd(&data, &data.commands[0]);
		//free_data(&data);
		free(input);
	}
	//free_arr2D(data.envp);
	return (0);
}
