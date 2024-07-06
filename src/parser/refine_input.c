/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:55:34 by darotche          #+#    #+#             */
/*   Updated: 2024/07/07 00:56:07 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*refine_input(char *input, t_data *data)
{
	char	*clean_and_expanded_line;
	char	*line_copy;
	char	*line_copy_2;

	if (sub_dub_quotes(input, data) || sub_sin_quotes(input, data))
		return (NULL);
	line_copy = replace_tabs_with_spaces(input);
	line_copy_2 = handle_missing_spaces(line_copy);
	clean_and_expanded_line = expand_input_str(line_copy_2, data);
	//free(line_copy);
	return (clean_and_expanded_line);
}
