#include "minishell.h"

int is_expansion(char **args) //find expansion in args
{
	int i;

	i = 0;
	while(args[i])
	{
		if (args[i][0] == '$')
		{
			//printf(YEL "'$' found: %s\n" RESET, args[i]);
			return(1);
		}
		i++;
	}
	return(0);
}