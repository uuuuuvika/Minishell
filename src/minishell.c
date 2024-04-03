#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	static t_data data;
    static t_envs envs;

    (void)argc;
    (void)argv;
    data.envp = envp;
 
    while (1)
    {
        char *input = readline(YEL "Minishell > " RESET);
        parse(input, &data);
        if (input != NULL)
            add_history(input);
        //validate_cmds();
        cpy_envs(&data, &envs);
        // if (data.num_of_children == 1)
        // {
        //     printf(YEL "Executing simple cmd in main\n" RESET);
        //     exec_cmd(&data, data.commands);
        // }
        // else
            pipe_cmds(&data, &envs);
        free(input);
    }
    return (0);
}
