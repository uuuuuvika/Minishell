#include "minishell.h"
// TODO: add libft
// TODO: builtins
// TODO: parse input
// TODO: execute

int main(int argc, char *argv[], char **envp)
{
    static t_data data;

    (void)argc;
    (void)argv;
    data.envp = envp;

    while (1)
    {
        char *input = readline(YEL "Minishell > " RESET);
        parse(input, &data);
        pipe_it(&data);
        //exec_cmd(&data, &data.commands[0]);
        // if (ft_strcmp(input, "echo") == 0)
        // {
        //     ft_echo("-n", data.envp);
        //     printf("NEW LINE?\n");
        //     //ft_pwd();
        //   //  break;
        // }
        //free(input);
    }
    return (0);
}

// int main()
// {
//     pid_t pid;
//     int i = 0;
//     char *paths[] = {"/bin/ls", "/bin/cat"};
//     char *cmd_1[] = {"ls", NULL};
//     char *cmd_2[] = {"cat", NULL};
//     char ***commands;

//     int pipes[2];
//     pipe(pipes);

//     printf("pipe[0]: %d\n", pipes[0]);
//     printf("pipe[1]: %d\n", pipes[1]);

//     commands = malloc(2 * sizeof(char **));
//     commands[0] = cmd_1;
//     commands[1] = cmd_2;
//     // while (1)
//     // {
//        // char *input = readline(YEL "Minishell > " RESET);

//         while (i < 2)
//         {
//             pid = fork();

//             if (pid == -1)
//             {
//                 perror("fork error");
//                 return (1);
//             }
//             if (pid == 0)
//             {
//                 // if (strcmp(input, "ls") == 0)
//                 // {
//                 if(i == 0)
//                 {
//                     //close it bc we dont use it, bc we dont need to read from it (just write)
//                     //writing end is 1
//                     //reading end is 0
//                     close(pipes[0]);

//                     dup2(pipes[1], 1);
//                     close(pipes[1]);
//                 }
//                 if(i == 1)
//                 {
//                     close(pipes[1]);
//                     dup2(pipes[0], 0);
//                     close(pipes[0]);
//                 }
//                 if (execve(paths[i], commands[i], NULL) == -1)
//                 {
//                     perror("execve");
//                     exit(1);
//                 }
//                 //}
//             }
//             // else
//             // {
//             //     wait(NULL);
//             // }
//             i++;
//             //close(pipes[1]);
//         }
//     wait(NULL);
//     //waitpid;
//         //free(input);
//     //}

//     close(pipes[0]);
//     close(pipes[1]);
//     return 0;
// }
