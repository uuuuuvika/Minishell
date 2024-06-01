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

void process_arg(char **arg, t_data *data)
{
	if (ft_strcmp(*arg, "$?") == 0)
		*arg = ft_itoa(data->exit_code);
	else if ((*arg)[0] == '$' && ft_strchr(*arg, '\'') == 0)
	{
		char *env_name = ft_strdup(*arg + 1);
		if (ft_getenv(env_name, data->envs) != NULL)
			replace_for_expansion(arg, ft_getenv(env_name, data->envs));
		else
			*arg = "\0";
		free(env_name);
	}
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
				process_arg(&split[j], data);
				j++;
			}
			char *tmp = arr2D_to_str(split);
			free(args[i]);
			args[i] = ft_strdup(tmp);
			free(tmp);
		}
		else
			process_arg(&args[i], data);
		i++;
	}
}