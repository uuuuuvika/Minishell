#include "minishell.h"

// CMD LINES FOR TESTING:

// darotche@c4b5c1:~$ $PWD $?
// bash: /home/darotche: Is a directory

// darotche@c4b5c1:~$ $? $TERM
// 126: command not found

// try:
// export VAR2='echo 123'

/// We do not need to handle this "echo "$(whoami)"""
// pass ? as a cmd and later in exec_cmd replace it for data->exit code
// Find somewhere to split the expanded string for example when ls -l

int is_multi_words(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

// void replace_for_expansion(char **args, char *cmd)
// {
// 	free(*args);
// 	*args = ft_strdup(cmd);
// }

void replace_for_expansion(char **args, char *cmd, t_data *data)
{
	free(*args);
	if (is_multi_words(cmd))
	{
		//char **split = ft_split(cmd, ' ');
		//printf("split[0]: %s\n", split[0]);
		// printf("split[1]: %s\n", split[1]);
		int fd[2];
		pipe(fd);
		pid_t pid;
		char readbuffer[10000];

		if ((pid = fork()) < 0)
		{
			printf("Fork error: %s\n", strerror(errno));
		}
		else if (pid == 0)
		{
			char **argv = ft_split(cmd, ' ');
			close(fd[0]);
			dup2(fd[1], 1);
			char *path = find_path(argv[0], data);
			execve(path, argv, data->envs);
			close(fd[1]);
			printf("Shouldn't execute this\n");
			exit(1);
		}
		else
		{
			wait(NULL);
			read(fd[0], readbuffer, sizeof(readbuffer));
			//printf("Received string: %s", readbuffer);
			*args = ft_strdup(readbuffer);
			close(fd[0]);
			close(fd[1]);
		};
	}
	else if (cmd[0] == '$')
	{
		char *env_name = ft_strdup(cmd + 1);
		//printf(RED "INSIDE env_name: %s\n" RESET, env_name);
		if (ft_getenv(env_name, data->envs) != NULL)
			//replace_for_expansion(&split[j], ft_getenv(env_name, data->envs), data);
			*args = ft_strdup(ft_getenv(env_name, data->envs));
		else
			*args = ft_strdup(cmd);
		free(env_name);
	}
	else
		*args = ft_strdup(cmd);
	printf("!!!!!! args: %s\n", *args);
}

char *arr2D_to_str(char **args)
{
	char *str;
	int i;

	str = NULL;
	i = 0;
	while (args[i])
	{
		str = ft_strjoin(str, args[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	free_arr2D(args);
	return (str);
}

void expand_arg(char **args, int num_args, t_data *data)
{
	(void)num_args;
	int i = 0;
	if ((ft_strlen(args[0]) == 1 && ft_strcmp(args[0], "$") == 0))
		return;
	while (args[i])
	{
		if (is_multi_words(args[i]))
		{
			char **split = ft_split(args[i], ' ');
			int j = 0;
			while (split[j])
			{
				// printf("split[j]: %s\n", split[j]);
				if (ft_strcmp(split[j], "$?") == 0)
				{
					if (g_signal == 2)
					{
						data->exit_code = 130;
						g_signal = 0;
						printf(MAG "-minishell: %d: command not found \n" WHT, data->exit_code);
						data->exit_code = 127;
					}
					split[j] = ft_itoa(data->exit_code); /// Check this later for proper allocation
					return;
				}
				else if (split[j][0] == '$')
				{
					char *env_name = ft_strdup(split[j] + 1);
					//printf(RED "env_name: %s\n" RESET, env_name);
					if (ft_getenv(env_name, data->envs) != NULL)
						replace_for_expansion(&split[j], ft_getenv(env_name, data->envs), data);
					else
						split[j][0] = '\0';
					free(env_name);
				}
				j++;
			}
			// print_2D(split);
			char *tmp = arr2D_to_str(split);
			// printf(MAG "tmp: %s\n" RESET, tmp);
			free(args[i]);
			args[i] = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			if (ft_strcmp(args[i], "$?") == 0)
			{
				if (g_signal == 2)
				{
					data->exit_code = 130;
					g_signal = 0;
					// printf(RED "-minishell: %d: command not found \n" WHT, data->exit_code);
					// data->exit_code = 127;
				}
				args[i] = ft_itoa(data->exit_code);
				return;
			}
			else if (args[i][0] == '$')
			{
				char *env_name = ft_strdup(args[i] + 1);
				//printf(RED "env_name: %s\n" RESET, env_name);
				if (ft_getenv(env_name, data->envs) != NULL)
					replace_for_expansion(&args[i], ft_getenv(env_name, data->envs), data);
				else
					args[i] = "\0";
				free(env_name);
			}
		}
		i++;
	}
}