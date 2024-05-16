#include "minishell.h"

int is_expansion(char **args)
{
	int i;

	i = 0;
	while(args[i])
	{
		if (ft_strchr(args[i], '$'))
		{
			//printf(YEL "'$' found: %s\n" RESET, args[i]);
			return(0);
		}
		i++;
	}
	return(1);
}