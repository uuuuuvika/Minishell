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
        if (input != NULL)
            add_history(input);
        //validate_cmds();
        if (data.num_of_children == 1)
        {
            printf(YEL "Executing simple cmd in main\n" RESET);
            exec_cmd(&data, data.commands);
        }
        else
            pipe_cmds(&data);
        free(input);
    }
    return (0);
}
