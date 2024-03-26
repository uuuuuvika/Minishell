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
char *cmd;
char **args;
int num_args;
int pipe_in; //-1
int pipe_out; // <pipe fd>
int redirect_in;
int redirect_out;
//bool has_built_in;
struct s_command *next;
} t_cmd;


typedef struct s_data{
    char **envp;
    int exit_code;
    int num_of_children;
    //char **piped_commands;
    int pipes[10][2];
    char **sub;
    t_cmd *commands;
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
int     ft_strcmp(const char *str1, const char *str2);
char	**ft_split(char const *s, char c);

void	free_arr2D(char **arr2D);
void	free_command(t_cmd *command);
void	free_commands(t_cmd *commands);
void	free_data(t_data *data);

void    ft_echo(char *flag, char **str);
void    ft_env(t_data data);
void    ft_pwd();

int     parse(char *input, t_data *data);
int     pipe_it(t_data *data);
char    *create_path(char *cmd);
void    exec_cmd(t_data *data, char *const argv[]);

int check_NULL(char *str);
void sub_quot(char *line_copy, t_data *data);

#endif