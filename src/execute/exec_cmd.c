#include "minishell.h"

void exec_cmd(t_data *data, t_cmd *cmd, t_envs *envs)
{
    char *path;

    check_NULL(cmd->args[0]);
    if (is_builtin(cmd) == 1)
    {
        if (ft_strcmp(cmd->args[0], "cd") == 0)
            ft_cd(data, cmd);
        else if (ft_strcmp(cmd->args[0], "echo") == 0)
            ft_echo(data, cmd);
        else if (ft_strcmp(cmd->args[0], "env") == 0)
            ft_env(data);
        else if (ft_strcmp(cmd->args[0], "pwd") == 0)
            ft_pwd(data);
        else if (ft_strcmp(cmd->args[0], "unset") == 0)
            ft_unset(envs, cmd);
        else if (ft_strcmp(cmd->args[0], "export") == 0)
            ft_export(data, cmd);
        else if (ft_strcmp(cmd->args[0], "exit") == 0)
            ft_exit(data, cmd);
    }
    else
    {
        path = create_path(cmd->args[0]);
    //    printf(GRN "Non-builtin \n" RESET);
        if (execve(path, cmd->args, data->envp) == -1)
        {
            printf(RED "Execve broke\n" RESET);
            exit(1);
        }
    }
}

// void exec_cmd(t_data *data, char *cmd)
// {
//     char *path;

//     if (cmd == NULL)
//     {
//         printf(RED "Something is wrong. 'null' is being passed as cmd\n" RESET);
//         exit (1);
//     }

//     else if (ft_strcmp(cmd, "cd") == 0)
//         ft_cd(data, data->commands->args[1]);
//     else if (ft_strcmp(cmd, "echo") == 0)
//         ft_echo(data, data->commands->args);
//     else if (ft_strcmp(cmd, "env") == 0)
//     {
//         printf(GRN "Executing builtin env\n" RESET);
//         ft_env(*data);
//     }
//     // else if (ft_strcmp(cmd[0], "exit") == 0)
//     // {
//     //     printf("Executing builtin exit\n");
//     //     ft_exit();
//     // }
//     // else if (ft_strcmp(cmd[0], "export") == 0)
//     // {
//     //     printf("Executing builtin export\n");
//     //     ft_export();
//     // }
//     else if (ft_strcmp(cmd, "pwd") == 0)
//     {
//         //printf(GRN "Executing builtin pwd\n" RESET);
//         ft_pwd(data);
//     }
//     // else if (ft_strcmp(cmd[0], "unset") == 0)
//     // {
//     //     printf(GRN"Executing builtin unset\n"RESET);
//     //     ft_unset();
//     // }
//     else if (is_builtin(cmd) == 0) //Why is it exiting after non builtins????
//     {
//         path = create_path(cmd);
//         printf(GRN "Non-builtin \n" RESET);
//         //prototype: int execve(const char *path, char *const argv[], char *const envp[]);
//         if (execve(path, data->commands->args, data->envp) == -1)
//             {
//                 perror("execve");
//                 exit(EXIT_FAILURE);
//             }
//    }
//     //exit(0);
// }