#include "minishell.h"

// TODO: write our own strcmp

int is_buildin(char *token)
{
    int valid = 0;
    int i = 0;
    char *E[] = {"echo", "cd", "pwd", "env", "exit", "export", "unset", NULL};

    while (E[i] != NULL)
    {
        if (strcmp(token, E[i]) == 0)
        {
            valid = 1;
            break;
        }
        i++;
    }
    return valid;
}

int parse_input(char *input)
{
    char *line = strdup(input);
    char *token;

    token = strtok(line, " \t\n\r");

    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, " \t\n\r");
        // if (strcmp(token, "|") == 0)
        //     printf("Found a pipe!\n");
        if (is_buildin(token))
            printf("Found a builtin command!\n");
    }
    return 0;
}

// int main()
// {
//     // char input[100];
//     char *ls_path = "/bin/ls";
//     char *ls_args[] = {"ls", NULL};

//     // char *term_type = getenv("TERM");

//     while (1)
//     {
//         char *input = readline(YEL "Minishell > " RESET);

//         if (strcmp(input, "ls") == 0)
//         {
//             if (execve(ls_path, ls_args, NULL) == -1)
//             {
//                 perror("execve");
//                 return (1);
//             }
//         }
//         // printf("yo! you entered: %s\n", input);
//         parse_input(input);
//         free(input);
//     }

//     return 0;
// }

int main()
{
    pid_t pid;
    int i = 0;
    char *paths[] = {"/bin/ls", "/bin/cat"};
    char *cmd_1[] = {"ls", NULL};
    char *cmd_2[] = {"cat", NULL};
    char ***commands;

    int pipes[2];
    pipe(pipes);

    printf("pipe[0]: %d\n", pipes[0]);
    printf("pipe[1]: %d\n", pipes[1]);

    commands = malloc(2 * sizeof(char **));
    commands[0] = cmd_1;
    commands[1] = cmd_2;
    // while (1)
    // {
       // char *input = readline(YEL "Minishell > " RESET);

        while (i < 2)
        {
            pid = fork();

            if (pid == -1)
            {
                perror("fork error");
                return (1);
            }
            if (pid == 0)
            {
                // if (strcmp(input, "ls") == 0)
                // {
                if(i == 0)
                {
                    //close it bc we dont use it, bc we dont need to read from it (just write)
                    //write is 1
                    //read is 0
                    close(pipes[0]);

                    dup2(pipes[1], 1);
                    close(pipes[1]);
                }
                if(i == 1)
                {
                    close(pipes[1]);
                    dup2(pipes[0], 0);
                    close(pipes[0]);
                }
                if (execve(paths[i], commands[i], NULL) == -1)
                {
                    perror("execve");
                    exit(1);
                }
                //}
            }
            // else
            // {
            //     wait(NULL);
            // }
            i++;
            //close(pipes[1]);
        }
    wait(NULL);
    //waitpid;
        //free(input);
    //}

    close(pipes[0]);
    close(pipes[1]);
    return 0;
}

// fgets(input, sizeof(input), stdin);
// input[strcspn(input, "\n")] = '\0';

// int parsing()
// {
//     if EOL
//         break;
//     split ('\t', '\n', '\r', ' ')
//     if word
//         token =word + '\0';
//         token ++;
//     if line = empty
//         ignore
//     if (token  = MAXARGS)

//     if (line[] = & )
//         run in bg
//     return bg
// }

// Simple built in commands: echo, echo -n, cd, pwd, export, unset, env,exit
// Compound commands
// < > >>  Redirections for stdin and stdout
// | output from one program to the input of the next program
// ; is used for program sequencing
// "" '' Quotes
// $PATH Enviroment variables
// ctrl-C, ctrl-D, ctrl-\  SIGINT, EOG, SIGQUIT
// $? should work like in bash
// Use up and down arrows to navigate through the command using termcap (mandatory) history which we will then be able to edit
// (at least like we can for classic lines if we feel like it (the line, not the history).

// & run programs in bg (not mandatory)

// Built in commands
//  echo
//  echo -n
//  cd
//  pwd
//  export
//  unset
//  env
//  exit
