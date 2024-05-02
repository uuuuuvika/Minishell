#include "minishell.h"

//static int g_signal;

int	main(int argc, char *argv[], char **envp)
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
        if(!input || errno == EINVAL)
		{
			printf("you have pressed CTRL-D\n");
			break;
		}
		if (input != NULL)
			add_history(input);
		parse(input, &data);
    	// validate_cmds();
        if (data.num_of_children == 1 && is_builtin(data.commands))
        {
            printf(YEL "Executing simple cmd in main\n" RESET);
			if (data.commands->redirect_in != -1)
            {
                if (dup2(data.commands->redirect_in, STDIN) == -1)
                    handle_error("dup2 error redirect_in");
                close(data.commands->redirect_in);
            }

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
	    free(input);
    }
    return (0);
}
