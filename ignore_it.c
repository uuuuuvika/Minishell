#include "minishell.h"


//parser back-up
//printf("num_of_children: %d\n", data->num_of_children);

    // t_cmd *current = data->commands;
    // t_cmd *previous = NULL;
    // while (current)
    // {
    //     if (previous)
    //     {
    //         int p[2];
    //         pipe(p);
    //         previous->pipe_out = p[PIPE_WRITE];
    //         current->pipe_in = p[PIPE_READ];
    //     }
    //     previous = current;
    //     current = current->next;
    // }

    // t_cmd *current = data->commands;
    // // t_cmd *previous = NULL;
    // while (current)
    // {
    //     printf("num_args: %d\n", current->num_args);
    //     printf("cmd: %s\n", current->args[0]);
    //     printf("redirect_in: %d\n", current->redirect_in);
    //     printf("redirect_out: %d\n", current->redirect_out);
    //     printf("pipe_in: %d\n", current->pipe_in);
    //     printf("pipe_out: %d\n", current->pipe_out);
    //     //previous = current;
    //     current = current->next;
    // }






// int main(int argc, char *argv[], char **envp) //main with allocated memory for data
// {

//     (void)argc;
//     (void)argv;

//     while (1)
//     {
//         t_data *data = malloc(sizeof(t_data));
//         //add error handling
//         data->envp = envp;
//         data->exit_code = 0;
//         data->num_of_children = 0;
//         data->sub = NULL;
//         data->commands = malloc(10 * sizeof(t_cmd));//replace 10 with a macro
//         char *input = readline(YEL "Minishell > " RESET);
//         parse(input, data);
//         // validate_cmds();
//         // if (data->num_of_children == 1)
//         // {
//         //     printf(YEL "Executing simple cmd in main\n" RESET);
//         //     exec_cmd(data, data->commands);
//         // }
//         // else
//         pipe_cmds(data);
//         free_data(data, input);
//     }
//     return (0);
// }

 extern char **environ;

// tree structure 
// typedef enum CommandType
// {
//     CMD_SIMPLE,
//     CMD_PIPE,
//     CMD_REDIRECT
// } CommandType;

// typedef struct Command
// {
//     CommandType type;
//     // it means that the union can only hold one of the members at a time
//     union
//     {
//         struct
//         {
//             char *cmd;      // Command string
//             char *flags;    // Flags maybe?
//             char **args;    // Array of arguments
//             int num_args;   // Number of arguments
//         } simple;

//         struct
//         {
//             struct Command *left; // Left side of pipe 
//             struct Command *right; // Right side of pipe
//         } pipe;

//         struct
//         {
//             struct Command *cmd; // Command to be redirected
//             int input;
//             int output;
//         } redirect;
//     } data;
// } Command;

//parse the input (very basic)
int parse_input(char *input)
{
    char *line_copy;
    char *token;

    if (input == NULL)
    {
        printf("Error! Input is NULL.\n");
        return -1;
    }

    line_copy = strdup(input);

    if (line_copy == NULL)
    {
        printf("Error!\n");
        return -1;
    }

    token = strtok(line_copy, " \t\n\r");

    while (token != NULL)
    {
        printf("%s\n", token);

        if (is_builtin(token))
        {
            printf(RED "Found a builtin command --> %s\n" RESET, token);
            if (strcmp(token, "exit") == 0)
            {
                printf("Exiting minishell...\n");
                exit(0);
            }
            //uses forbiden global variable, oops
            if (strcmp(token, "env") == 0)
            {
                printf("Printing environment variables...\n");
                for (char **current = environ; *current; current++)
                {
                    puts(*current);
                }
                return 0;
            }
        }

        if (strcmp(token, "|") == 0)
            printf(RED "Found a pipe!\n" RESET);

        token = strtok(NULL, " \t\n\r");
    }

    free(line_copy);
    return 0;
}

//Hanneses forks and pipes
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

// fgets(input, sizeof(input), stdin);
// input[strcspn(input, "\n")] = '\0';

