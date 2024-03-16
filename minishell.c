#include "minishell.h"

// TODO: write our own strcmp


int main()
{
    // char input[100];
    char *ls_path = "/bin/ls";
    char *ls_args[] = {"ls", NULL};

    // char *term_type = getenv("TERM");

    while (1)
    {
        char *input = readline(YEL "Minishell > " RESET);

        if (strcmp(input, "ls") == 0)
        {
            if (execve(ls_path, ls_args, NULL) == -1)
            {
                perror("execve error");
                return (1);
            }
        }
        // printf("yo! you entered: %s\n", input);
        parse_input(input);
        free(input);
    }

    return 0;
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
//                     //write is 1
//                     //read is 0
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

// fgets(input, sizeof(input), stdin);
// input[strcspn(input, "\n")] = '\0';

