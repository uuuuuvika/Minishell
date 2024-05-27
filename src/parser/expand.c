#include "minishell.h"

// CMD LINES FOR TESTING

// darotche@c4b5c1:~$ $PWD $?
// bash: /home/darotche: Is a directory

// darotche@c4b5c1:~$ $? $TERM
// 126: command not found

// try:
//export VAR2='echo 123'

void replace_for_expansion(char **args, char *cmd)
{
	// char *env_name;
	
	// env_name = ft_strdup(*args + 1);
	// free(env_name);
	free(*args);
	*args = ft_strdup(cmd);
	//printf(GRN "Valid env: args: %s\n" RESET ,*args);
}

void expand_arg(char **args, int num_args, t_data *data)
{
	int i;
	(void)data;
	(void)num_args;
	i = 0;
	if(ft_strlen(args[0]) == 1 && (ft_strcmp(args[0], "$"))==0)
	{
		args[i] = ft_strdup("$");
		return;
	}
	// if(ft_strcmp(args[0], "$?") == 0)
	// {
	// 	args[i] = ft_strdup("$?"); //printf("cmd is $?\n");// pasms ? as a cmd and later in exec_cmd replace it for data->exit code
	// 	return;
	// }
	////// Find somewhere to split the expanded string for example when ls -l
	while (args[i] && is_expansion(args) == 0)
	{
		if (args[i][0] != '$')
			i++;
		char *env_name = ft_strdup(args[i] + 1);
		if(getenv(env_name) != NULL)
		{	
			replace_for_expansion(&args[i], getenv(env_name));
			free(env_name);
			break;
		}
		/*else
		{
			printf(RED"env not found: %s \n" RESET, env_name);
			if(num_args == 1)
			{
				args[i] = ft_strdup("");
				free(env_name);
				break;
			}
			if(ft_strcmp(args[i], "$?") == 0) ///Replace for exit code since we can do 'echo $?'
			{
				//printf(YEL"cmd is $?\n" RESET);// pass ? as a cmd and later in exec_cmd replace it for data->exit code
				//args[i] = ft_strdup("$?");
				args[i] = ft_itoa(data->exit_code);
				free(env_name);
				break;
			}
			int j = i;
			free(args[j++]);
			while (args[j])
			{
				args[j-1] = ft_strdup(args[j]);
				j++;
				free(env_name);
			}
			args[j - 1] = NULL;
		}
	}
	//rm_quotes_arr(args);*/
	}
	//return (NULL);
}