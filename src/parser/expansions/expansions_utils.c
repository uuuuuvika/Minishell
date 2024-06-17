#include "minishell.h"

int is_multi_words(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void replace_for_expansion(char **args, char *cmd)
{
	free(*args);
	*args = ft_strdup(cmd);
}

// might need it for the future
// if (cmd[0] == '$')
// 	{
// 		char *env_name = ft_strdup(cmd + 1);
// 		if (ft_getenv(env_name, data->envs) != NULL)
// 			*args = ft_strdup(ft_getenv(env_name, data->envs));
// 		else
// 			*args = ft_strdup(cmd);
// 		free(env_name);
// 	}