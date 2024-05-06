#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	static t_data data;
	//data.exit_code = 0;
	char	*input;
	
    (void)argc;
    (void)argv;

    cpy_envs(&data, envp);
    while (1)
    {
        handle_ctrl();
        input = readline(YEL "Minishell > " RESET);
        if(!input || errno == EINVAL)
		{
			printf("you have pressed CTRL-D\n");
			break;
		}
		if (input != NULL)
			add_history(input);
		parse(input, &data);
    	// validate_cmds();
        if ((data.num_of_children == 1 && is_builtin(data.commands)) || (data.num_of_children == 1 && ft_strcmp(data.commands->args[0], "$?") == 0))
        {
            printf(YEL "Executing simple builtin in main\n" RESET);
			// if (data.commands->redirect_in != -1)
            // {
            //     if (dup2(data.commands->redirect_in, STDIN) == -1)
            //         handle_error("dup2 error redirect_in");
            //     close(data.commands->redirect_in);
            // }

            if (data.commands->redirect_out != -1)
            { 
                if (dup2(data.commands->redirect_out, STDOUT) == -1)
                    handle_error("dup2 error redirect_out");
                close(data.commands->redirect_out);
            }
			exec_cmd(&data, data.commands);
        }
		else
		{
			printf(YEL "Fork\n" RESET);
        	pipe_cmds(&data);
		}
		printf("exit code in main is %d\n", data.exit_code);
		//printf("g_signal in main is %d\n", g_signal);
	    free(input);
    }
    return (0);
}