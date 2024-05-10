#include "minishell.h"

// darotche@c4b5c1:~$ $PWD $?
// bash: /home/darotche: Is a directory
// darotche@c4b5c1:~$ $? $TERM
// 126: command not found


char *expand_arg(char **args, int num_args)
{
	char *cmd;
	int i;

	i = 0;
	if(ft_strlen(args[0]) == 1 && (ft_strcmp(args[0], "$"))==0)// if only '$' pass ? as a cmd and later replace it for data->exit code
	{
		//cmd == "$"; //We print '$: command not found'
		//printf("cmd is $\n");
		args[i] = ft_strdup("$");
		return(0);
	}
	if(ft_strcmp(args[0], "$?") == 0)/// check input "$?aaa"
	{
		printf("cmd is ?\n");// pass ? as a cmd and later in exec_cmd replace it for data->exit code
		args[i] = ft_strdup("$?");
		return(0);
	}
	while (args[i] && args[i][0] == '$')
	{
		printf("---------------Enter loop i = %d \n", i);
		char *env_name = ft_strdup(args[i] + 1);
		printf("envname is %s\n", env_name);
		if(getenv(env_name) != NULL)
		{
			cmd = getenv(env_name);
			printf("cmd is now: %s\n", cmd);
			free(args[i]);
			args[i] = ft_strdup(cmd);
			printf(RED "args[i]: %s\n" RESET ,args[i]);
			break;
		}
		else if(getenv(env_name) == NULL)
		{
			if(num_args == 1)
			{
				printf("return empty str\n");
				args[i] = ft_strdup("");
				break;
			}
			int j = i;
			printf("j is %d\n", j);
			free(args[j++]);
			while (args[j])
			{
				printf("args[j] is %s,\n", args[j]);
				args[j-1] = ft_strdup(args[j]);
				j++;
			}
			printf("args[j] is %s,\n", args[j]);
			printf("i is %d\n", i);
			args[j - 1] = NULL;
		}
	}
	return(NULL);
}
