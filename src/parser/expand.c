#include "minishell.h"

// CMD LINES FOR TESTING:

// darotche@c4b5c1:~$ $PWD $?
// bash: /home/darotche: Is a directory

// darotche@c4b5c1:~$ $? $TERM
// 126: command not found

// try:
//export VAR2='echo 123'

///We do not need to handle this "echo "$(whoami)"""


void replace_for_expansion(char **args, char *cmd)
{
	// char *env_name;

	// env_name = ft_strdup(*args + 1);
	// free(env_name);
	free(*args);
	*args = ft_strdup(cmd);
}

char *expand_arg(char **args, int num_args, t_data *data)
{
	int i;
	(void)num_args;
	i = 0;
	if (ft_strlen(args[0]) == 1 && (ft_strcmp(args[0], "$")) == 0)
		return (NULL);
	// pasms ? as a cmd and later in exec_cmd replace it for data->exit code
	if (ft_strcmp(args[0], "$?") == 0)
		return (NULL);
	////// Find somewhere to split the expanded string for example when ls -l
	if (!is_expansion(args))
		return (NULL);
	while (args[i])
	{
		if (args[i][0] == '$' && ft_strchr(args[i], '\'') == 0)
		{
			char *env_name = ft_strdup(args[i] + 1);
			printf(BLU"env_name: %s\n" RESET, env_name);
			if (ft_getenv(env_name, data->envs) != NULL)
			{
				printf(GRN"Valid env: %s\n" RESET, env_name);
				replace_for_expansion(&args[i], ft_getenv(env_name, data->envs));
				free(env_name);
				break;
			}
			else if (ft_strcmp(args[i], "$?") == 0) /// Replace for exit code since we can do 'echo $?'
			{
				// printf(YEL"cmd is $?\n" RESET);// pass ? as a cmd and later in exec_cmd replace it for data->exit code
				// args[i] = ft_strdup("$?");
				args[i] = ft_itoa(data->exit_code);
				free(env_name);
				break;
			}
			else
			{
				printf(RED"Not valid env: %s \n" RESET, env_name);
				free(env_name);
				args[i][0] = '\0';
				// 	if (num_args == 1)
				// 	{
				// 		args[i][0] = '\0';
				// 		free(env_name);
				// 		break;
				// 	}
				// 	if (ft_strcmp(args[i], "$?") == 0) /// Replace for exit code since we can do 'echo $?'
				// 	{
				// 		// printf(YEL"cmd is $?\n" RESET);// pass ? as a cmd and later in exec_cmd replace it for data->exit code
				// 		// args[i] = ft_strdup("$?");
				// 		args[i] = ft_itoa(data->exit_code);
				// 		free(env_name);
				// 		break;
				// 	}
				// 	int j = i;
				// 	free(args[j++]);
				// 	while (args[j])
				// 	{
				// 		args[j - 1] = ft_strdup(args[j]);
				// 		j++;
				// 		free(env_name);
				// 	}
				// 	args[j - 1] = NULL;
			}
		}
		else
			i++;
		// i++;
	}
	// rm_quotes_arr(args);
	return (NULL);
}