#include "minishell.h"

// void write_error(const char *msg)
// {
//     write(2, msg, ft_strlen(msg)); // 2 is the file descriptor for stderr
// }

// void	error_messages(char *cmd)
// {
// 	if (errno == ENOENT) {
//             write_error("minishell: ");
//             write_error(cmd);
//             write_error(": command not found\n");
//         } else if (errno == EACCES) {
//             write_error("minishell: ");
//             write_error(cmd);
//             write_error(": permission denied\n");
//         } else if (errno == ENOTDIR) {
//             write_error("minishell: ");
//             write_error(cmd);
//             write_error(": not a directory\n");
//         } else if (errno == EISDIR) {
//             write_error("minishell: ");
//             write_error(cmd);
//             write_error(": is a directory\n");
//         } else if (errno == ENAMETOOLONG) {
//             write_error("minishell: ");
//             write_error(cmd);
//             write_error(": file name too long\n");
//         } else {
//             write_error("minishell: ");
//             write_error(cmd);
//             write_error(": ");
//             write_error(strerror(errno));
//             write_error("\n");
//         }
// }

void	exec_builtin(t_data *data, t_cmd *cmd)
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

void	exec_cmd(t_data *data, t_cmd *cmd)
{
    char	*path;

	if(cmd->num_args == 0)
	{
		printf("minishell: : command not found\n");
		return;
	}
    int i = 0;
    while(ft_strcmp(cmd->args[i] , "") == 0 && cmd->args[i + 1] != NULL)
        i++;
    if (is_builtin(cmd->args[i]))
		exec_builtin(data, cmd);
	else
	{
		//Check if it will be cmd not found or is directory
		path = find_path(cmd->args[i], data);
		if (!path)
		{
			write_error("minishell: ");
			write_error(cmd->args[i]);
			write_error(": command not found\n");
			return;
        }
		execve(path, cmd->args, data->envs);
    //    error_messages(cmd->args[i]);
	}
}