#ifndef MINISHELL_H
#define MINISHELL_H
#define MAXARGS 128
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RESET "\033[0m"

// #include "libft.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_command {
char *cmd;
char **args;
int num_args;
int pipe_in;
int pipe_out;
int redirect_in;
int redirect_out;
//bool has_built_in;
struct s_command *next;
} t_command;


typedef struct s_data{
    char **envp;
    int exit_code;
    int num_of_children; //maybe?
    //char **piped_commands;
    char **sub;
    t_command *commands;
} t_data;

// ls -l " | grep foo > output.txt "
// ls -l "fffffffffffffffffffff"

// +----------+
// | command|
// | cmd: "ls"
// | args: ["-l", NULL]
// | pipe_out: <pipe fd> | next: --+
// | +----------+

// | command |
// | cmd: "grep"
// | args: ["foo", NULL]
// | pipe_in: <pipe fd>
// | redirect_out: <output.txt fd> | next: NULL
// +----------+

int ft_strcmp(const char *str1, const char *str2);

int parse_input(char *input);
void ft_echo(char *flag, char **str);
void ft_env(t_data data);
void ft_pwd();

int parse(char *input, t_data *data);

char	**ft_split(char const *s, char c);

#endif