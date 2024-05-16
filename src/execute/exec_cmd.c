#include "minishell.h"

void	exec_cmd(t_data *data, t_cmd *cmd)
{
    char	*path;

    check_NULL(cmd->args[0]);
    if (is_builtin(cmd))
    {
        if (ft_strcmp(cmd->args[0], "cd") == 0)
            ft_cd(data, cmd);
        else if (ft_strcmp(cmd->args[0], "echo") == 0)
            ft_echo(data, cmd);
        else if (ft_strcmp(cmd->args[0], "env") == 0)
            ft_env(data);
        else if (ft_strcmp(cmd->args[0], "pwd") == 0)
            ft_pwd(data);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
            ft_export(data, cmd);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
            ft_unset(data, cmd);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
            ft_exit(data);
    }
    else if (ft_strcmp(cmd->args[0], "$?") == 0)
	{
		if(g_signal == 2)
		{
			data->exit_code = 130;
			g_signal = 0;
		}
		printf(RED "-minishell: %d: command not found \n" WHT, data->exit_code);
	}
	else
	{
		path = create_path(cmd->args[0], data);
		execve(path, cmd->args, data->envs);
	}
}
