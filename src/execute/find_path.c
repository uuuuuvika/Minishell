#include "minishell.h"

char    *find_path(char *cmd, t_data *data)
{
	char        *path;
    char        **paths;
    struct stat statbuf;

	//printf(BLU "PATH: %s\n" RESET, ft_getenv("PATH", data->envs));
	paths = ft_split(ft_getenv("PATH", data->envs), ':');
	int i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (stat(path, &statbuf) == 0)
		{
			//free_arr2D(paths); //comment bc it was giving me a double free error
			return (path);	
		}
		i++;
	}
	//free_arr2D(paths); //comment bc it was giving me a double free error
    free(path);
	printf("-minishell: %s: command not found \n", cmd);// This error is for commands
	//add printferror for ("-minishell: %s: No such file or directory \n", cmd), there are some errors "Permision denied" w exit code 126(cmd found but not executable)
    data->exit_code = 127;
    return (NULL);
}