#include "minishell.h"

char *expand_input(char *line_copy, t_data *data)
{
	//char *expanded_line;
	//machar *command;
	(void)data;
	//Check if is expansion

	char **arg = ft_split(line_copy, ' ');

	while(arg)
	{
		if(ft_strncmp(*arg, "$", 1))
		{
			if(ft_strncmp(*arg, "$?", 2) == 0)
				printf("cmd is ?\n");// pass ? as a cmd and later replace it for data->exit code
			if(ft_strlen(line_copy) == 1)
			{
				printf("cmd is $\n");
			// 	cmd == "$"; We print '$: command not found'
			}
			else //Check if first arg is valid
			{
				char *env_name = ft_strdup(*arg + 1);
				printf("envname is %s\n", env_name);
				char *env_value = ft_strdup(getenv(env_name));
				printf("env value is %s\n", env_value);
				if(env_value == NULL)
				{
					printf("env_value does not exist\n"); //Clear input and print prompt again
					//if (arg[1])//if there is second arg pass it as a cmd;
					//	cmd ==arg [1];
					//finish
				}
				//	cmd == value;
			//	free(env_name);
			//	free(env_value);
				//finish
			}
		}
		// else
		// {
		// 	if(is_valid_cmd(arg))
		// 	{
		// 		//clear_line();

		// 		command = arg; //assign arg to cmd;
		// 	}
		arg++;
	}
	//expanded_line = replace_line_copy();
	return("expanded_line");
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