/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:44:59 by darotche          #+#    #+#             */
/*   Updated: 2024/07/02 13:25:52 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_dollar_question(char **arg, t_data *data)
{
	if (g_signal == 2)
	{
		data->exit_code = 130;
		g_signal = 0;
	}
	char *tmp = ft_itoa(data->exit_code);
	replace_for_expansion(arg, tmp);
	free(tmp);
}

void expand_env_variable(char **arg, t_data *data)
{
	char *env_name;
	char *env_value;

	env_name = ft_strdup(*arg + 1);
	env_value = ft_getenv(env_name, data->envs);
	if (env_value != NULL)
		replace_for_expansion(arg, env_value);
	else
		(*arg)[0] = '\0';
	free(env_name);
	free(env_value);
}

void expand_multiple_args(char **split, t_data *data)
{
	int j;

	j = 0;
	while (split[j])
	{
		if (ft_strcmp(split[j], "$?") == 0)
		{
			expand_dollar_question(&split[j], data);
			return;
		}
		else if (split[j][0] == '$')
			expand_env_variable(&split[j], data);
		j++;
	}
}

int count_dsqm(char **arg)
{
	int i = 0;
	int count = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '$' && (*arg)[i + 1] == '?')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

void expand_single_arg(char **arg, t_data *data)
{
    int i = 0;
    int j = 0;
    int count = 0;
    char *result;
    char *tmp;

    if ((*arg)[0] == '$' && (*arg)[1] != '?')
        expand_env_variable(arg, data);
    else
    {
        count = count_dsqm(arg);
        if (count > 0)
        {
            result = ft_strdup("");
            while ((*arg)[i])
            {
                if ((*arg)[i] == '$' && (*arg)[i + 1] == '?')
                {
                    tmp = ft_substr(*arg, j, i - j);
                    result = ft_strjoin(result, tmp);
                    free(tmp);
                    tmp = ft_itoa(data->exit_code);
                    result = ft_strjoin(result, tmp);
                    free(tmp);
                    i += 2;
                    j = i;
                }
                else
                    i++;
            }
            tmp = ft_substr(*arg, j, i - j);
            result = ft_strjoin(result, tmp);
            free(tmp);

            free(*arg);
            *arg = result;
        }
    }
}


void expand_arg(char **args, t_data *data)
{
	int i;
	char **split;
	char *tmp;

	i = 0;
	while (args[i])
	{
		if (!is_all_dollars(args[i]))
		{
			if (is_multi_words(args[i]))
			{
				split = ft_split(args[i], ' ');
				expand_multiple_args(split, data);
				tmp = arr2D_to_str(split);
				free(args[i]);
				args[i] = ft_strdup(tmp);
				free(tmp);
			}
			else
				expand_single_arg(&args[i], data);
		}
		i++;
	}
}
