#ifndef MINISHELL_H
# define MINISHELL_H
# define MAXARGS 128
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\033[0m"

//#include "libft.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

// enum builtin_t
// {
//     echo,
//     cd,
//     pwd,
//     env,
//     exit,
//     export,
//     unset
// };


// struct command
// {
//     int argc;
//     char *argv[MAXARGS];
//     enum builtin_t { NONE, QUIT, JOBS, BG, FG} builtin:
//     //enum builtin_t {EXEC, REDIRECT, PIPE, LIST, BACK} builtin:
// };

// // |
// struct cmd {
//     int type;
// };

// struct exec_cmd {

// }

// struct pipe_cmd
// {
//     left 
//     right
// }
// // ;
// struct list_cmd
// {
//     left 
//     right
// }
// //&
// struct back
//     cmd

// // execute

// //redirect

#endif