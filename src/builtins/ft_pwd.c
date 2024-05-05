#include "minishell.h"

void ft_pwd(t_data *data)
{
        (void) data;
        char cwd[MAXPATHLEN];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
            printf( "%s\n", cwd);
			data->exit_code = 0;
		}
		else
        	perror("getcwd error");
}