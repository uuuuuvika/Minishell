/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:20:09 by vshcherb          #+#    #+#             */
/*   Updated: 2024/06/27 15:10:43 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAXARGS 128
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define PIPE_READ 0
# define PIPE_WRITE 1
# define SIGINT
# define SIGQUIT
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\033[0m"

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <sys/fcntl.h>
# include <readline/history.h>
# include <errno.h>
# include <termios.h>

extern int	g_signal;

typedef struct s_cmd
{
	char			**args;
	int				num_args;
	int				pipe_in;
	int				pipe_out;
	int				redirect_in;
	int				redirect_out;
	int				here_doc;
	int				here_doc_exp;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int		exit_code;
	int		num_of_children;
	char	**sub;
	char	**subb;
	char	**envs;
	int		cmn_here_doc;
	t_cmd	*commands;
}	t_data;

void	write_error(const char *msg);
int		handle_error(const char *message);
int		check_null(char *str);
void	free_arr2D(char **arr2D);
void	free_data(t_data *data);
void	free_main(t_data *data, char *input);

char	*find_path(char *cmd, t_data *data);
void	exec_cmd(t_data *data, t_cmd *cmd);
int		is_builtin(char *command);

void	ft_cd(t_data *data, t_cmd *cmd);
void	ft_echo(t_data *data, t_cmd *cmd, int i);
void	ft_env(t_data *data);
void	ft_pwd(t_data *data);
void	ft_unset(t_data *data, t_cmd *cmd, int i);
void	ft_export(t_data *data, t_cmd *cmd, int i);
void	ft_exit(t_data *data);

char	*ft_getenv(char *env_name, char **envs);
char	*get_env_name(char *s, char c);
int		count_env(char **envp);
int		cpy_envs(t_data *data, char **envp);

void	pipe_assign(t_cmd *command);
int		pipe_cmds(t_data *data);

int		parse(char *input, t_data *data);
char	*refine_input(char *input, t_data *data);
t_cmd	*create_cmd_node(char *input);
void	add_cmd_to_list(t_cmd **head, t_cmd *new_node);
void	args_realloc(t_cmd *new_node);
int		handle_redirects(t_cmd *new_node, t_data *data, char **future_children);

void	redirect_fd_dup(t_cmd *command, t_data *data);
int		is_redirect(char *str);
int		cnt_args(char **args);
int		redirect_assign(t_cmd *cmd, t_data *data);

int     sub_sin_quotes(char *line_copy, t_data *data);
void	return_sin_quotes(char **args, t_data *data);
int     sub_dub_quotes(char *line_copy, t_data *data);
void	return_dub_quotes(char **args, t_data *data);
int     sub_quotes(char *line_copy, t_data *data);

void	expand_arg(char **args, t_data *data);
void	expand_env_variable(char **arg, t_data *data);
void	expand_multiple_args(char **split, t_data *data);
void	expand_dsqm(char **arg, t_data *data);
int		is_expansion(char **args);
int		is_all_dollars(char *str);
void	replace_for_expansion(char **args, char *cmd);
char	*expand_input_str(char *line, t_data *data);
int		is_multi_words(char *str);
int     count_dsqm(char **arg);

void	fd_close(t_cmd *command);
void	ultimate_fd_close(t_data *data);
void	ultimate_wait(t_data *data, pid_t *pid);
void	fd_dup2(t_cmd *command);


void    read_heredoc(char *delimiter, t_cmd *current, t_data *data);
void    read_heredoc_simple(char *delimiter, t_data *data);
int     heredoc_preprocess(t_cmd *new_node, t_data *data);
char    *split_expand_join(char *line, t_data *data);
char	*split_expand_join(char *line, t_data *data);

void	print_envs(t_data *data);
void	print_2D(char **args);
void	print_cmd_nodes(t_data *data);

char	*arr2D_to_str(char **args);

int		cnt_missing_space(char *line);
char	*add_space_to_redirect(char *input);
char	*replace_tabs_with_spaces(char *line);
char	*handle_missing_spaces(char *line);

void	sig_handler(int sig);
void	handle_keypress(void);
void	sig_handler_fork(int sig);
void	handle_keypress_fork(t_data *data);

int		is_space(char c);
int		is_str_space(char *str);
int		is_dsqm(t_cmd *cmd);
void	print_banner(void);
void	print_banner_2(void);

#endif
