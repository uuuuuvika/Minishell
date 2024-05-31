#include "minishell.h"


// void expand_arg(char **args, int num_args, t_data *data)
// {
// 	int i;
// 	(void)data;
// 	(void)num_args;
// 	i = 0;
// 	if(ft_strlen(args[0]) == 1 && (ft_strcmp(args[0], "$"))==0)
// 	{
// 		args[i] = ft_strdup("$");
// 		return;
// 	}
// 	// if(ft_strcmp(args[0], "$?") == 0)
// 	// {
// 	// 	args[i] = ft_strdup("$?"); //printf("cmd is $?\n");// pasms ? as a cmd and later in exec_cmd replace it for data->exit code
// 	// 	return;
// 	// }
// 	////// Find somewhere to split the expanded string for example when ls -l
// 	while (args[i] && is_expansion(args) == 0)
// 	{
// 		if (args[i][0] != '$')
// 			i++;
// 		char *env_name = ft_strdup(args[i] + 1);
// 		if(getenv(env_name) != NULL)
// 		{
// 			replace_for_expansion(&args[i], getenv(env_name));
// 			free(env_name);
// 			break;
// 		}
// 		else
// 		{
// 			printf(RED"env not found: %s \n" RESET, env_name);
// 			if(num_args == 1)
// 			{
// 				args[i] = ft_strdup("");
// 				free(env_name);
// 				break;
// 			}
// 			if(ft_strcmp(args[i], "$?") == 0) ///Replace for exit code since we can do 'echo $?'
// 			{
// 				//printf(YEL"cmd is $?\n" RESET);// pass ? as a cmd and later in exec_cmd replace it for data->exit code
// 				//args[i] = ft_strdup("$?");
// 				args[i] = ft_itoa(data->exit_code);
// 				free(env_name);
// 				break;
// 			}
// 			int j = i;
// 			free(args[j++]);
// 			while (args[j])
// 			{
// 				args[j-1] = ft_strdup(args[j]);
// 				j++;
// 				free(env_name);
// 			}
// 			args[j - 1] = NULL;
// 		}
// 	//}
// 	//rm_quotes_arr(args);*/
// 	}
// 	//return (NULL);
// }


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

void replace_for_expansion(char **args, char *cmd)
{
	free(*args);
	*args = ft_strdup(cmd);
}

char *expand_arg(char **args, int num_args, t_data *data)
{
	int i;
	(void)num_args;
	i = 0;
	if (ft_strcmp(args[0], "$?") == 0)
	{
		if(g_signal == 2)
		{
			data->exit_code = 130;
			g_signal = 0;
		printf(RED "-minishell: %d: command not found \n" WHT, data->exit_code);
		data->exit_code = 127; // So when we call $? after "-minishell: 130: command not found" it changes to "(..)127: command(..)""
		}
		args[i] = ft_itoa(data->exit_code);
		return (NULL);
	}
	if ((ft_strlen(args[0]) == 1 && ft_strcmp(args[0], "$") == 0) || ft_strcmp(args[0], "$?") == 0 || !is_expansion(args))
		return (NULL);
	while (args[i])
	{
		if (args[i][0] == '$' && ft_strchr(args[i], '\'') == 0)
		{
			char *env_name = ft_strdup(args[i] + 1);
			// printf("env_name: %s\n", env_name);
			if (ft_getenv(env_name, data->envs) != NULL)
			{
				// printf(GRN"Valid env: %s\n" RESET, env_name);
				replace_for_expansion(&args[i], ft_getenv(env_name, data->envs));
			}
			else if (ft_strcmp(args[i], "$?") == 0) // Replace for exit code since we can do 'echo $?'
			{
				// printf(YEL"cmd is $?\n" RESET);
				args[i] = ft_itoa(data->exit_code);
			}
			else
				args[i][0] = '\0';
			free(env_name);
		}
		else
			i++;
	}
	return (NULL);
}