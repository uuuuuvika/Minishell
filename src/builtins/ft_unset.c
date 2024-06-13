#include "minishell.h"

void remove_env(t_data *data, char *arg)
{
    int i;

    i = 0;
    while (data->envs[i] != NULL)
    {
        if (ft_strncmp(data->envs[i], arg, ft_strlen(arg)) == 0)
        {
            free(data->envs[i++]);
            while (data->envs[i] != NULL)
            {
                data->envs[i-1] = ft_strdup(data->envs[i]);
                i++;
            }
            data->envs[i - 1] = NULL;
            return;
        }
        i++;
    }
}

void ft_unset(t_data *data, t_cmd *cmd)
{
    int i;

    i = 1;
    while (cmd->args[i] != NULL)
    {
        remove_env(data, cmd->args[i]);
        i++;
    }
	data->exit_code = 0;
}
