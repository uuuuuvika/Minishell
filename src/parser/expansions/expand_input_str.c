/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:22:47 by darotche          #+#    #+#             */
/*   Updated: 2024/06/21 02:12:18 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_line(char *line, t_data *data)
{
    char **split;
    char *env;
    char *new_line;
    int i;

    split = ft_split(line, ' ');
    
    // if (ft_getenv(&split[0][1], data->envs) == NULL)
    //     return;

    i = 0;
    while (split[i])
    {
        if (split[i][0] == '$')
        {
            env = ft_getenv(split[i] + 1, data->envs);
            if (env)
            {
                free(split[i]);
                split[i] = ft_strdup(env);
            }
        }
        i++;
    }

    new_line = arr2D_to_str(split);
    return (new_line);
}