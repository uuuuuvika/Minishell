#include "minishell.h"

// void exec_ls(char *str)
// {
//     char *args[] = {"ls", "-l", NULL}; //
//     if (strcmp(str, "ls") == 0)
//     {
//         if (execve("/bin/ls", args, envp) == -1)
//         {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     }
// }

void exec_cmd(t_data *data, t_command *command)
{
    char *path;

    // if (ft_strcmp(cmd[0], "cd") == 0)
    // {
    //     printf("Executing builtin cd\n");
    //     ft_cd();
    // }    
    if (ft_strcmp(command->args[0], "echo") == 0)
    {
        printf("Executing builtin echo\n");
        ft_echo(command->args[1], command->args);
    }    
    if (ft_strcmp(command->args[0], "env") == 0)
    {
        printf(GRN"Executing builtin env\n"RESET);
        ft_env(*data);
    }    
    // else if (ft_strcmp(cmd[0], "exit") == 0)
    // {
    //     printf("Executing builtin exit\n");
    //     ft_exit();
    // }  
    // else if (ft_strcmp(cmd[0], "export") == 0)
    // {
    //     printf("Executing builtin export\n");
    //     ft_export();
    // }  
    else if (ft_strcmp(command->args[0], "pwd") == 0)
    {
        printf(GRN"Executing builtin pwd\n"RESET);
        ft_pwd();
    }
    // else if (ft_strcmp(cmd[0], "unset") == 0)
    // {
    //     printf(GRN"Executing builtin unset\n"RESET);
    //     ft_unset();
    // }
    else
    {
        printf(GRN"Non-builtin, creating path\n"WHT);
        path = create_path(command->args[0]);
        //prototype: int execve(const char *path, char *const argv[], char *const envp[]);
        if (execve(path, command->args, data->envp) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
   }
  //  exit(0);
}