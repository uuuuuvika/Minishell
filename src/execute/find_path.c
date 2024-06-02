#include "minishell.h"

char *find_path(char *cmd, t_data *data)
{
	char *path;
	char **paths;
	struct stat statbuf;

	if (stat(cmd, &statbuf) == 0)
		return (cmd);
	if (ft_strcmp(cmd, "") == 0)
		printf("-minishell: : command not found \n"); // This is a bit of a cheat code, if we have time we should make it better :)
	paths = ft_split(ft_getenv("PATH", data->envs), ':');
	int i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (stat(paths[i], &statbuf) == 0)
		{
			path = ft_strdup(paths[i]);
			free_arr2D(paths);
			return (path);
		}
		i++;
	}
	free_arr2D(paths);
	printf(BLU "-minishell: %s: command not found \n" RESET, cmd); // This error is for commands														   // add printferror for ("-minishell: %s: No such file or directory \n", cmd), there are some errors "Permision denied" w exit code 126(cmd found but not executable)
	data->exit_code = 127;
	return (NULL);
}