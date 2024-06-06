#include "minishell.h"

int	cpy_envs(t_data *data, char **envp)
{
	int	count;

	data->envs = ft_calloc(count_env(envp) + 1, sizeof(char *));
	if (!data->envs)
	{
		perror(RED "Calloc failed\n" RESET);
		return (1);
	}
	count = 0;
	while (envp[count])
	{
		data->envs[count] = ft_strdup(envp[count]);
		count++;
	}
	return (0);
}
