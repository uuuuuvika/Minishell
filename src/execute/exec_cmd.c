#include "minishell.h"

int	exec_cmd(t_data *data, t_cmd *cmd)
{
    char	*path;

    check_NULL(cmd->args[0]);
    // if (is_builtin(cmd))
    // {
    //     if (strcmp(cmd->args[0], "cd") == 0)
    //         ft_cd(data, cmd);
    //     else if (strcmp(cmd->args[0], "echo") == 0)
    //         ft_echo(data, cmd);
    //     else if (strcmp(cmd->args[0], "env") == 0)
    //          ft_env(data);
    //     else if (strcmp(cmd->args[0], "pwd") == 0)
    //         ft_pwd(data);
	// 	else if (strcmp(cmd->args[0], "export") == 0)
    //         ft_export(data, cmd);
	// 	else if (strcmp(cmd->args[0], "unset") == 0)
    //         ft_unset(data, cmd);
	// 	else if (strcmp(cmd->args[0], "exit") == 0)
    //         ft_exit(data);
    // }
    // else if (strcmp(cmd->args[0], "$?") == 0)
	// {
	// 	if(g_signal == 2)
	// 	{
	// 		data->exit_code = 130;
	// 		g_signal = 0;
	// 	}
	// 	printf(RED "-minishell: %d: command not found \n" WHT, data->exit_code);
	// }
	//else
	//{
		path = create_path(cmd->args[0], data);
		if (path == NULL)
			return (data->exit_code);
		execve(path, cmd->args, data->envs);
	//}
	return (0);
}



// void replace_exit_code(char** args, int last_exit_code)
// {
// 	int i;

// 	i = 0;
// 	//printf("g_signal: %d \n",  g_signal);
// 	while(args[i])
// 	{
// 		if (g_signal == 2 && ft_strcmp(args[0], "$?") == 0)
// 		{
// 			data->exit_code = 130;
// 			g_signal = 0;
// 		}
// 		//printf("%d\n", data->exit_code);

// 		if (ft_strcmp(args[i], "$?") == 0)
// 		{
// 			char exit_code_str[10] = ft_itoa(last_exit_code);
// 			free(args[i]);
// 			args[i] = ft_strdup(exit_code_str);
// 			printf("exit code in exec %d\n", data->exit_code);
// 			printf("cmd after exec_cmd %s\n", cmd->args[0]);
// 			printf("exit_code_str %s\n", exit_code_str);

// 			free(cmd->args[0]); // Free memory allocated by strdup
// 			cmd->args[0]= exit_code_str;
// 			printf(YEL "-minishell: %s: command not found \n" WHT, cmd->args[0]);
// 		}
// 		i++;
// 	}
// }