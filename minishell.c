#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char input[100];
    char *ls_path = "/bin/ls";
    char *ls_args[] = {"ls", NULL};

    while (1)
    {
        printf(YEL "Minishell > " RESET);
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "ls") == 0)
        {
            if (execve(ls_path, ls_args, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}

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
