#ifndef MINISHELL_H
#define MINISHELL_H
#define MAXARGS 128
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define PIPE_READ 0
#define PIPE_WRITE 1
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
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_command {
char **args;
int num_args;
int pipe_in; //-1
int pipe_out; // <pipe fd>
int redirect_in;
int redirect_out;
struct s_command *next;
} t_command;


typedef struct s_data{
    char **envp;
    int exit_code;
    int num_of_children; //maybe?
    //char **piped_commands;
    char **sub;
    int pipes[10][2];
    t_command *commands;
} t_data;

// ls -l " | grep foo > output.txt "
// ls -l "fffffffffffffffffffff"

// +----------+
// | command|
// | cmd: "ls"
// | args: ["-l", NULL]
// | pipe_out: <pipe fd> 
// | next: --+
// | +----------+

// | command |
// | cmd: "grep"
// | args: ["foo", NULL]
// | pipe_in: <pipe fd>
// | redirect_out: <output.txt fd> 
// | next: NULL
// +----------+

char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
int     ft_strcmp(const char *str1, const char *str2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
int     is_builtin(char *token);

void    ft_cd(t_data *data, char *new_path);
void    ft_echo(t_data *data, char **args);
void    ft_env(t_data data);
void    ft_pwd(t_data *data);
//void    ft_exit();
//void    ft_unset();
//void    ft_exit();

int     parse(char *input, t_data *data);
int     pipe_it(t_data *data);
char    *create_path(char *cmd);
void    exec_cmd(t_data *data, char *command);
//void    exec_cmd(t_data *data, char *args[]);


#endif