#include "minishell.h"

int ft_isalldigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


void ft_exit(t_data *data)
{
	if (data->commands->num_args > 1)
	{
		if (data->commands->num_args > 2)
		{
			perror("minishell: exit: too many arguments\n");
			data->exit_code = 1;
			return;
		}
		else if (ft_isalldigit(data->commands->args[1]) == 0)
		{
			//printf("minishell: exit: %s: numeric argument required\n", data->commands->args[1]);
			perror("minishell: numeric argument required\n");
		}
		else
			data->exit_code = ft_atoi(data->commands->args[1]);
	}
	else
		data->exit_code = 0;
	free_arr2D(data->envs);
    free_arr2D(data->sub);
    free_arr2D(data->subb);
    free_data(data);
    clear_history();
    //need to check & free it properly
    exit(errno);
}
