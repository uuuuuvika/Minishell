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
#include <sys/fcntl.h>
#include <readline/history.h>
#include <errno.h>

extern int g_signal;

typedef struct s_cmd {
    char **args;
    int num_args;
    int pipe_in; //-1
    int pipe_out; // <pipe fd>
    int redirect_in;
    int redirect_out;
    struct s_cmd *next;
} t_cmd;

typedef struct s_data {
    int exit_code;
    int num_of_children;
    char **sub;
    t_cmd *commands;
    char  **envs;
} t_data;

int     handle_error(const char *message);
int     check_NULL(char *str);
void	free_arr2D(char **arr2D);
void    free_data(t_data *data);
// void	free_command(t_cmd *command);
// void	free_commands(t_cmd *commands);
// void	free_data(t_data *data);

void    ft_cd(t_data *data, t_cmd *cmd);
void    ft_echo(t_data *data, t_cmd *cmd);
void    ft_env(t_data *data);
void    ft_pwd(t_data *data);
void    ft_unset(t_data *data, t_cmd *cmd);
void    ft_export(t_data *data, t_cmd *cmd);
void    ft_exit(t_data *data);

int     parse(char *input, t_data *data);
void    redirect_fd_dup(t_cmd *command);
int     pipe_cmds(t_data *data);
char	*expand_arg(char **args, int num_args);
char    *create_path(char *cmd, t_data *data);
int     exec_cmd(t_data *data, t_cmd *cmd);
int     is_builtin(t_cmd *command);

int     count_env(char **envp);
int     cpy_envs(t_data *data, char **envp);
void	print_envs(t_data *data);

int     parse(char *input, t_data *data);
void    sub_dub_quotes(char *line_copy, t_data *data);
int     is_redir(char *str);
int     cnt_args(char **args);
void    pipe_assign(t_cmd *command);
void    redirect_assign(t_cmd *cmd);

void	sig_handler(int sig);
void	handle_ctrl(void);

int     pipe_cmds(t_data *data);

void    fd_close(t_cmd *command);
void    ultimate_fd_close(t_data *data);
void    ultimate_wait(t_data *data, pid_t *pid);
void    fd_dup2(t_cmd *command);

#endif