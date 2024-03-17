#include "minishell.h"

int print_env(pid_t pid)
{
    char input[10];
    
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strcmp(input, "pwd") == 0)
    {
        printf(CYN"Im only a child and my pid is: %d \n" RESET, pid);
        printf("%s\n",getenv("PATH"));
    }
    else
        printf("minishell: %s:  command not found\n", input);
    exit(0);
}

int main()
{
    char *args[1000] = {"hola"};
    printf(CYN"🐚 minishell$ "RESET);
    ft_echo(NULL, args);
    return(0);
}
    // parse_cmdline();//remember to null terminate
    // get_tocken():
    // execute_cmdline()
    // {
    //     if (is builtin)
    //         builtin_cmd():
    //     else
    //     {
    //         system_cmd()
    //         pid_t childPid;
    //         childPid = fork();
    //         // Execute commands 
    //         execvp();
    //         // int execvp(const char *file, char *const argv[]);
    //         // or we keep the child in bg 
    //         //or make parent wait();
    //     }
   //  }
   //return (0);

    

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


//Built in commands
// echo
// echo -n
// cd
// pwd 
// export 
// unset
// env 
// exit 
