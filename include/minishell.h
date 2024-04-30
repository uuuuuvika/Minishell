#ifndef MINISHELL_H
#define MINISHELL_H
#define MAXARGS 128
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define PIPE_READ 0
#define PIPE_WRITE 1
#define SIGINT
#define SIGQUIT
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RESET "\033[0m"

#include "libft.h"
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

typedef struct s_envs{
    char **var;
  //  int num_var;
} t_envs;

typedef struct s_cmd {
    char **args;
    int num_args;
    int pipe_in; //-1
    int pipe_out; // <pipe fd>
    int redirect_in;
    int redirect_out;
    struct s_cmd *next;
    t_envs  *envs;
} t_cmd;

typedef struct s_data{
    int exit_code;
    int num_of_children;
    //char **piped_commands;
    int pipes[10][2];
    char **sub;
    t_cmd *commands;
    t_envs  *envs;
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

// char	*ft_strjoin(char *s1, char *s2);
// size_t	ft_strlen(const char *str);
// int     ft_strcmp(const char *str1, const char *str2);
// int     ft_strncmp(const char *s1, const char *s2, size_t n);
// size_t	ft_strlcpy(char *dest, const char *src, size_t size);
// char	**ft_split(char const *s, char c);
// char	*ft_strdup(char const *s);

void	free_arr2D(char **arr2D);
void	free_command(t_cmd *command);
void	free_commands(t_cmd *commands);
void	free_data(t_data *data);

void    ft_cd(t_data *data, t_cmd *cmd);
void    ft_echo(t_data *data, t_cmd *cmd);
void    ft_env(t_data *data);
void    ft_pwd(t_data *data);
void    ft_unset(t_data *data, t_cmd *cmd);
void    ft_export(t_data *data, t_cmd *cmd);
void    ft_exit(t_data *data);

int     parse(char *input, t_data *data);
int     pipe_cmds(t_data *data);
char    *create_path(char *cmd);
void    exec_cmd(t_data *data, t_cmd *cmd);
int     is_builtin(t_cmd *command);

int     count_env(char **envp);
int     cpy_envs(t_data *data, char **envp);
void	print_envs(t_data *data);

int     check_NULL(char *str);
void    sub_quot(char *line_copy, t_data *data);

void	sig_handler();

#endif