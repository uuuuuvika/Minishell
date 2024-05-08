#include "minishell.h"

char *expand_arg(char *input)
{
	char *expanded_arg = "";
	int i;
	i = 0;
	//Check if is expansion
	//cmd == "$"; We print '$: command not found'
	// if only '$' pass ? as a cmd and later replace it for data->exit code

	//while args
	//When no command clear input and print prompt again
	//when args is a command pass only this command
	if(input[0] != '$')
	{
		expanded_arg = ft_strdup(input);
		return(expanded_arg);
	}
	if(ft_strlen(input) == 1 && (ft_strncmp(input, "$", 1))==0)
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
	{ ///Find first valid env and replace env_name for env_value, keep all following arguments
		char *cmd;
		char **args = ft_split(input, ' ');
		while(args[i])
		{
			char *env_name = ft_strdup(args[i] + 1);
			printf("envname is %s\n", env_name);
			//char *env_value = ft_strdup(getenv(env_name));
			//printf("env value is %s\n", env_value);
			if(getenv(env_name) != NULL || ft_strcmp(args[i], "pwd") == 0)
			{
				while(args[i])
				{
					if(getenv(env_name) != NULL)
						cmd = getenv(env_name);
					else if(ft_strcmp(args[i], "pwd") == 0)
						cmd = "pwd";
					printf("args now: %s\n", args[i]);
					printf("cmd is now: %s\n", cmd);
					expanded_arg = strcat(cmd, expanded_arg);
					printf(GRN "expanded_arg is now: %s\n" RESET, expanded_arg);
					i++;
					if (args[i] != NULL)
						expanded_arg = strcat(expanded_arg, " ");
				}
				if (args[i] == NULL)
					return(expanded_arg);
				cmd = "";
			}
			i++;
			printf(YEL "Go to next arg\n" RESET);
		}
			//	cmd == value;
		//	free(env_name);
		//	free(env_value);
			//finish
			// else
			// {
			// 	if(is_valid_cmd(arg))
			// 	{
			// 		//clear_line();

			// 		command = arg; //assign arg to cmd;
			// 	}
		//expanded_line = replace_line_copy();
	}
	return(0);
}



// void expand(char *line_copy, t_data *data)
// {
// 	char *expanded_line;
// 	(void)data;
// 	//Check if is expansion
// 	if(line_copy[0] == '$')
// 	{
// 		char **arg = ft_split(line_copy, ' ');
// 		if(ft_strcmp(arg[0], "$?") == 0)
// 			printf("cmd is ?\n");// pass ? as a cmd and later replace it for data->exit code
// 		if(ft_strlen(line_copy) == 1)
// 		{
// 			printf("cmd is $\n");
// 		// 	cmd == "$"; We print '$: command not found'
// 		}
// 		else //Check if first arg is valid
// 		{
// 			char *env_name = ft_strdup(arg[0] + 1);
// 			printf("envname is %s\n", env_name);
// 			char *env_value = ft_strdup(getenv(env_name));
// 			printf("env value is %s\n", env_value);
// 			if(env_value == NULL)
// 			{
// 				printf("env_value does not exist\n"); //Clear input and print prompt again
// 				//if (arg[1])//if there is second arg pass it as a cmd;
// 				//	cmd ==arg [1];
// 				//finish
// 			}
// 			//	cmd == value;
// 		//	free(env_name);
// 		//	free(env_value);
// 			//finish
// 		}
// 	}
// }