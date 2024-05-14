#include "minishell.h"

// CMD LINES FOR TESTING
// darotche@c4b5c1:~$ $PWD $?
// bash: /home/darotche: Is a directory
// darotche@c4b5c1:~$ $? $TERM
// 126: command not found


char *expand_arg(char **args, int num_args)
{
	char *cmd;
	int i;

	i = 0;
	if(ft_strlen(args[0]) == 1 && (ft_strcmp(args[0], "$"))==0)
	{
		args[i] = ft_strdup("$");
		return(0);
	}
	if(ft_strcmp(args[0], "$?") == 0)
	{
		//printf("cmd is $?\n");// pass ? as a cmd and later in exec_cmd replace it for data->exit code
		args[i] = ft_strdup("$?");
		return(0);
	}
	////// Find somewhere to split the expanded string for example when ls -l
	while (args[i] && args[i][0] == '$')
	{
		char *env_name = ft_strdup(args[i] + 1);
		if(getenv(env_name) != NULL)
		{
			cmd = getenv(env_name);
			//printf("cmd is now: %s\n", cmd);
			free(env_name);
			free(args[i]);
			args[i] = ft_strdup(cmd);
		//	printf(RED "valid cmd args[i]: %s\n" RESET ,args[i]);
			break;
		}
		else if(getenv(env_name) == NULL)
		{
			//printf("args[i] %s \n", args[i]);
			if(num_args == 1)
			{
				args[i] = ft_strdup("");
				free(env_name);
				break;
			}
			if(ft_strcmp(args[i], "$?") == 0)
			{
				//printf("cmd is $?\n");// pass ? as a cmd and later in exec_cmd replace it for data->exit code
				args[i] = ft_strdup("$?");
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
	rm_quotes(args[i]);
	return(NULL);
}
