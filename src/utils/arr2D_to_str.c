#include "minishell.h"

char *arr2D_to_str(char **args)
{
	char *str;
	int i;

	str = NULL;
	i = 0;
	while (args[i])
	{
		str = ft_strjoin(str, args[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	free_arr2D(args);
	return (str);
}