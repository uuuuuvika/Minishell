#include "minishell.h"

// darotche@c4b5c1:~$ $PWD $?
// bash: /home/darotche: Is a directory
// darotche@c4b5c1:~$ $? $TERM
// 126: command not found

char *expand_arg(char *input)
{
	char *expanded_arg = ft_strdup("");
	int i;
	i = 0;

	if(input[0] != '$')	//If no expansion, return same input
	{
		expanded_arg = ft_strdup(input);
		return(expanded_arg);
	}
	if(ft_strlen(input) == 1 && (ft_strncmp(input, "$", 1))==0)// if only '$' pass ? as a cmd and later replace it for data->exit code
	{
		//cmd == "$"; //We print '$: command not found'
		//printf("cmd is $\n");
		expanded_arg = ft_strdup("$");
		return(expanded_arg);
	}
	if(ft_strncmp(input, "$?", 2) == 0)/// check input "$?aaa"
	{
		// if (arg[0][3] != '\0')
		// 	split_arg(arg[0]);
		printf("cmd is ?\n");// pass ? as a cmd and later in exec_cmd replace it for data->exit code
		expanded_arg = ft_strdup("$?");
		return(expanded_arg);
	}
	else
	{ ///Find first valid env and replace env_name for env_value, keepm all following arguments
		char *cmd;
		char **args = ft_split(input, ' ');
		while(args[i])
		{
			printf("---------------Enter loop i = %d \n", i);
			if (args[i][0] == '$')
			{
				char *env_name = ft_strdup(args[i] + 1);
				printf("envname is %s\n", env_name);
				//char *env_value = ft_strdup(getenv(env_name));
				//printf("env value is %s\n", env_value);
				if(getenv(env_name) != NULL)
					cmd = getenv(env_name);
				else
					cmd = ft_strdup("");
				printf("cmd is now: %s\n", cmd);
			}
			else
				cmd = args[i];
			printf("args now: %s\n", args[i]);
			printf(GRN "cmd is now: %s\n" RESET, cmd);
			expanded_arg = strcat(expanded_arg, cmd);
			printf(GRN "expanded_arg is now: %s\n" RESET, expanded_arg);
			if (args[i] == NULL)
				return(expanded_arg);
			if (args[i+1] != NULL)
				expanded_arg = strcat(expanded_arg, " ");
			i++;
			printf(YEL "Go to next arg\n" RESET);
		}
	}
			//	cmd == value;
		//	free(env_name);
		//	free(env_value);
		//free input;

			//finish
			// else
			// {
			// 	if(is_valid_cmd(arg))
			// 	{
			// 		//clear_line();

			// 		command = arg; //assign arg to cmd;
			// 	}
		//expanded_line = replace_line_copy();
	printf(YEL "------------NO MORE ARGS, len: %zu\n" RESET,ft_strlen(expanded_arg));
	return(expanded_arg);
}


// char *expand_arg(char *input)
// {
// 	char *expanded_arg = ft_strdup("");
// 	int i;
// 	i = 0;

// 	if(input[0] != '$')	//If no expansion, return same input
// 	{
// 		expanded_arg = ft_strdup(input);
// 		return(expanded_arg);
// 	}
// 	if(ft_strlen(input) == 1 && (ft_strncmp(input, "$", 1))==0)// if only '$' pass ? as a cmd and later replace it for data->exit code
// 	{
// 		//cmd == "$"; //We print '$: command not found'
// 		//printf("cmd is $\n");
// 		expanded_arg = ft_strdup("$");
// 		return(expanded_arg);
// 	}
// 	if(ft_strncmp(input, "$?", 2) == 0)/// check input "$?aaa"
// 	{
// 		// if (arg[0][3] != '\0')
// 		// 	split_arg(arg[0]);
// 		printf("cmd is ?\n");// pass ? as a cmd and later in exec_cmd replace it for data->exit code
// 		expanded_arg = ft_strdup("$?");
// 		return(expanded_arg);
// 	}
// 	else
// 	{ ///Find first valid env and replace env_name for env_value, keepm all following arguments
// 		char *cmd;
// 		char **args = ft_split(input, ' ');
// 		while(args[i])
// 		{
// 			char *env_name = ft_strdup(args[i] + 1);
// 			printf("envname is %s\n", env_name);
// 			//char *env_value = ft_strdup(getenv(env_name));
// 			//printf("env value is %s\n", env_value);
// 			if(getenv(env_name) != NULL || ft_strcmp(args[i], "pwd") == 0)
// 			{
// 				while(args[i])
// 				{
// 					if(getenv(env_name) != NULL)
// 						cmd = getenv(env_name);
// 					else if(ft_strcmp(args[i], "pwd") == 0)
// 						cmd = "pwd";
// 					printf("args now: %s\n", args[i]);
// 					printf("cmd is now: %s\n", cmd);
// 					expanded_arg = strcat(cmd, expanded_arg);
// 					printf(GRN "expanded_arg is now: %s\n" RESET, expanded_arg);
// 					i++;
// 					if (args[i] != NULL)
// 						expanded_arg = strcat(expanded_arg, " ");
// 				}
// 				if (args[i] == NULL)
// 					return(expanded_arg);
// 				cmd = "";
// 			}
// 			i++;
// 			printf(YEL "Go to next arg\n" RESET);
// 		}
// 			//	cmd == value;
// 		//	free(env_name);
// 		//	free(env_value);
// 		//free input;

// 			//finish
// 			// else
// 			// {
// 			// 	if(is_valid_cmd(arg))
// 			// 	{
// 			// 		//clear_line();

// 			// 		command = arg; //assign arg to cmd;
// 			// 	}
// 		//expanded_line = replace_line_copy();
// 	}
// 	return(expanded_arg);
// }

