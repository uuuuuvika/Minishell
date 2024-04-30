#include "minishell.h"

int varname_len(char *var)
{
    int i;

	i = 0;
    while (var[i] && var[i] != '=')
		i++;
    return (i);
}

int var_cmp(char **envar, char *newvar)
{
    int i;

    i = 0;
    int j = 0;
    while (envar[i])
    {
        j = 0;
        if(varname_len(envar[i]) && varname_len(newvar))
        {
            while (j <= varname_len(envar[i]) && envar[i][j] == newvar[j])
            {
                // printf("j is %d ", j);
                // printf("varnamelen is %d\n", varname_len(envar[i]));
                // printf("envar is %c\n",envar[i][j]);
                // printf("newvar is %c\n",newvar[j]);
                if(envar[i][j] == '=' && newvar[j] == '=')
                    return(1);
                j++;
            }
        }
        i++;
    }
    return(0); 
}

int replace_var(t_data *data, t_cmd *cmd)
{
    int i;
    char **tmp;
    tmp = malloc(sizeof(char*) * (count_env(data->envs->var) + 1));
    if(tmp == NULL)
        return(-1);
    i = 0;
    while(data->envs->var[i] != NULL)
    {
        if(ft_strncmp(data->envs->var[i], cmd->args[1], varname_len(data->envs->var[i])) == 0)
        {
            tmp[i] = cmd->args[1];
            i++;
        }
        else
        {
            tmp[i] = ft_strdup(data->envs->var[i]);
            i++;
        }
    }
    tmp[i] = NULL;
    free_arr2D(data->envs->var);
    data->envs->var = tmp;
    return(0);
}

int	add_var(t_data *data, t_cmd *cmd)
{
	int i;
	int j;
	char **new_var;

	new_var = malloc(sizeof(char*) * (count_env(data->envs->var) + 2));
	if (new_var == NULL)
        return(-1);
	j = 0;
	while(cmd->args[j] != NULL)
	{
		i = 0;
		while(data->envs->var[i] != NULL)
		{
			new_var[i] = ft_strdup(data->envs->var[i]);
			i++;
		}
		new_var[i] = ft_strdup(cmd->args[j]);
		i++;
		new_var[i] = NULL;
		j++;
	}
	free(data->envs->var);
	data->envs->var = new_var;
	i = 0;
	while(new_var[i])
	{
		data->envs->var[i] = ft_strdup(new_var[i]);
		i++;
	}
	return(0);
}

void ft_export(t_data *data, t_cmd *cmd)
{
    int     i;
    int     j;

    i = 0;
    j = 1;
    check_NULL(cmd->args[1]); //neeed to check args format as well
    if(var_cmp(data->envs->var, cmd->args[j]) == 1)
    {
        printf(YEL "Replace variable\n" RESET);
        replace_var(data, cmd);
    }
    else
    {
        printf(YEL "Add a new variable\n" RESET);
		add_var(data, cmd);
    }
	//print_envs(data);
}
