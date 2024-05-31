#include "minishell.h"

int is_b(char *cmd)
{
    int i = 0;
    char *builtins[] = {"echo", "cd", "pwd", "env", "exit", "export", "unset", NULL};

    while (builtins[i] != NULL)
    {
        if (strcmp(cmd, builtins[i]) == 0)
        {
            return (1);
        }
        i++;
    }
    return (0);
}

void	exec_cmd(t_data *data, t_cmd *cmd)
{
    char	*path;

    // check_NULL(cmd->args[0]);
    int i = 0;
    while(ft_strcmp(cmd->args[i] , "") == 0 && cmd->args[i + 1] != NULL)
        i++;
    if (is_b(cmd->args[i]))
    {
        if (ft_strcmp(cmd->args[i], "cd") == 0)
            ft_cd(data, cmd);
        else if (ft_strcmp(cmd->args[i], "echo") == 0)
            ft_echo(data, cmd);
        else if (ft_strcmp(cmd->args[i], "env") == 0)
            ft_env(data);
        else if (ft_strcmp(cmd->args[i], "pwd") == 0)
            ft_pwd(data);
		else if (ft_strcmp(cmd->args[i], "export") == 0)
            ft_export(data, cmd);
		else if (ft_strcmp(cmd->args[i], "unset") == 0)
            ft_unset(data, cmd);
		else if (ft_strcmp(cmd->args[i], "exit") == 0)
            ft_exit(data);
    }
    else if (ft_strcmp(cmd->args[i], "$?") == 0)
	{
		if(g_signal == 2)
		{
			data->exit_code = 130;
			g_signal = 0;
		}
		printf(RED "-minishell: %d: command not found \n" WHT, data->exit_code);
		data->exit_code = 127; // So when we call $? after "-minishell: 130: command not found" it changes to "(..)127: command(..)""
	}
	else
	{
		//Check if it will be cmd not found or is directory
		path = find_path(cmd->args[i], data);
        printf(GRN "path: %s\n" RESET, path);
		execve(path, cmd->args, data->envs);
	}
}