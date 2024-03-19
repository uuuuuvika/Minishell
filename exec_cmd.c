#include "minishell.h"

// void exec_ls(char *str)
// {
//     char *args[] = {"ls", "-l", NULL}; // Argumentos para el comando ls
//     char *envp[] = {NULL}; // Variables de entorno (en este caso, ninguna)
//     if (strcmp(str, "ls") == 0)
//     {
//         if (execve("/bin/ls", args, envp) == -1)
//         {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     }
//   //  exit(0);
// }

//
void exec_cmd(t_data *data, t_command *cmd)
{
    char *path;
    //// First check_existing_cmd();
    //execve prototype: int execve(const char *path, char *const argv[], char *const envp[]);
    path = ft_strjoin("/bin/", cmd->args[0]);
    printf("path passed to execve: %s\n",path);
    if (execve(path, cmd->args, data->envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
  //  exit(0);
}