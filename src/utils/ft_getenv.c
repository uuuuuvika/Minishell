#include "minishell.h"

char *ft_getenv(char *env_name, char **envs)
{
	int i;
	char *env_value;

	i = 0;
	// printf("env_name: %s\n", env_name);
	while (envs[i])
	{
		if (ft_strncmp(envs[i], env_name, ft_strlen(env_name)) == 0 && envs[i][ft_strlen(env_name)] == '=')
		{
			env_value = ft_strdup(envs[i] + ft_strlen(env_name) + 1);
			printf(GRN "Valid env: %s\n" RESET, env_value);
			return (env_value);
		}
		i++;
	}
	return (NULL);
}