#include "minishell.h"

int varname_len(char *var)
{
    int i;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    return (i);
}

// int var_cmp(char **envar, char *newvar)
// {
//     int i = 0;
//     while (envar[i])
//     {
//         if ((varname_len(envar[i]) == varname_len(newvar)) && (ft_strncmp(envar[i], newvar, varname_len(envar[i])) == 0))
//             return (1);
//         i++;
//     }
//     return (0);
// }

int replace_var(char **envar, char *newvar)
{
    int i = 0;
    while (envar[i])
    {
        if ((varname_len(envar[i]) == varname_len(newvar)) && (ft_strncmp(envar[i], newvar, varname_len(envar[i])) == 0))
        {
            free(envar[i]);
            envar[i] = ft_strdup(newvar);
            return (1);
        }
        i++;
    }
    return (0);
}

int add_var(char ***envar, char *newvar)
{
    char **tmp;
    int i;
    
    tmp = malloc(sizeof(char *) * (count_env(*envar) + 2));
    i = 0;
    while ((*envar)[i])
    {
        tmp[i] = ft_strdup((*envar)[i]);
        i++;
    }
    tmp[count_env(*envar)] = ft_strdup(newvar);
    tmp[count_env(*envar) + 1] = NULL;
    free_arr2D(*envar);
    *envar = tmp;
    return (0);
}

void ft_export(t_data *data, t_cmd *cmd)
{
    int j;

    j = 1;
    if (cmd->num_args > 1)
	{
		if(cmd->args[j][0] == '=' || !ft_isalpha(cmd->args[1][0]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd->args[1]);
			data->exit_code = 1;
			return;
		}
		if(ft_strchr(cmd->args[j], '=') == NULL)
		{
			data->exit_code = 1;
			j++;
		}
	}
	while (cmd->args[j] != NULL)
    {
		print_2D(cmd->args);
        if(!replace_var(data->envs, cmd->args[j]))
        {
           // printf(GRN "Add variable\n" RESET);
            add_var(&data->envs, cmd->args[j]);
        }
        j++;
    }
	data->exit_code = 0;
}

//Check this
// darotche@c4b10c1:~$ export 45
// bash: export: `45': not a valid identifier
// darotche@c4b10c1:~$ $?
// 1: command not found
// darotche@c4b10c1:~$ 
