/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:46 by darotche          #+#    #+#             */
/*   Updated: 2024/07/02 14:31:01 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varname_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

int	replace_var(char **envar, char *newvar)
{
	int	i;

	i = 0;
	while (envar[i])
	{
		if ((varname_len(envar[i]) == varname_len(newvar))
			&& (ft_strncmp(envar[i], newvar, varname_len(envar[i])) == 0))
		{
			free(envar[i]);
			envar[i] = ft_strdup(newvar);
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_var(char ***envar, char *newvar)
{
	char	**tmp;
	int		i;

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

void	export_error_and_code(char *arg, t_data *data)
{
	write_error("minishell: export: ");
	write_error(arg);
	write_error(": not a valid identifier\n");
	data->exit_code = 1;
}

void	ft_export(t_data *data, t_cmd *cmd, int i)
{
	char	*env_name;

	i++;
    if (cmd->num_args > 1)
    {
		while (cmd->args[i] != NULL)
		{
			env_name = get_env_name(cmd->args[i], '=');
			if (!(ft_strchr(cmd->args[i], '=')) && ft_isallalpha(cmd->args[i]))
			{
				i++;
				return ;
			}
			else if (cmd->args[i][0] == '=' || !ft_isall_alnum(env_name) || ft_isall_digit(env_name) || ft_strchr(cmd->args[i], '=') == NULL)
			{
				export_error_and_code(cmd->args[i], data);
				free(env_name);
				return ;
			}
			if (ft_strchr(cmd->args[i], '=') == NULL)
			{
				data->exit_code = 1;
				i++;
			}
			free(env_name);
			if (!replace_var(data->envs, cmd->args[i]))
				add_var(&data->envs, cmd->args[i]);
			i++;
		}
    }
    data->exit_code = 0;
}

