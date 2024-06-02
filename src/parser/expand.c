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

void replace_for_expansion(char **args, char *cmd)
{
	free(*args);
	*args = ft_strdup(cmd);
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
						printf(RED "-minishell: %d: command not found \n" WHT, data->exit_code);
						data->exit_code = 127; // So when we call $? after "-minishell: 130: command not found" it changes to "(..)127: command(..)""
					}
					split[j] = ft_itoa(data->exit_code); /// Check this later for proper allocation
					return;
					// split[j] = ft_itoa(data->exit_code);
				}
				else if (split[j][0] == '$')
				{
					char *env_name = ft_strdup(split[j] + 1);
					// printf(RED "env_name: %s\n" RESET, env_name);
					if (ft_getenv(env_name, data->envs) != NULL)
						replace_for_expansion(&split[j], ft_getenv(env_name, data->envs));
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
					printf(RED "-minishell: %d: command not found \n" WHT, data->exit_code);
					data->exit_code = 127; // So when we call $? after "-minishell: 130: command not found" it changes to "(..)127: command(..)""
				}
				args[i] = ft_itoa(data->exit_code); /// Check this later for proper allocation
				return ;
			}
			else if (args[i][0] == '$')
			{
				char *env_name = ft_strdup(args[i] + 1);
				if (ft_getenv(env_name, data->envs) != NULL)
					replace_for_expansion(&args[i], ft_getenv(env_name, data->envs));
				else
					args[i] = "\0";
				free(env_name);
			}
		}
		i++;
	}
}