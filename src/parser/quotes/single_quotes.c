#include "minishell.h"

void	sub_sin_quotes(char *line_copy, t_data *data)
{
	int index = 0;
	int count_subs = 0;

	while (line_copy[index])
	{
		if (line_copy[index] == '\'')
			count_subs++;
		index++;
	}
	if (count_subs % 2 != 0)
	{
		char *del = "\'";
		read_heredoc_simple(del, data);
		return ;
	}

	data->subb = malloc(((count_subs / 2) + 1) * sizeof(char *));
	int s_index = 0;
	index = 0;
	while (line_copy[index])
	{
		if (line_copy[index] == '\'')
		{
			int k = index;
			while (line_copy[++k] != '\'')
				;
			int len = k - index;
			char *str = ft_calloc(len, sizeof(char));
			int str_index = 0;
			while (line_copy[++index] != '\'')
			{
				str[str_index++] = line_copy[index];
				line_copy[index] = '#';
			}
			data->subb[s_index++] = ft_strdup(str);
			free(str);
		}
		index++;
	}
	data->subb[s_index] = NULL;
}

void	return_sin_quotes(char **args, t_data *data)
{
	
	int i = 0;
	int t = 0;
	while (args[i])
	{
		int j = 0;
		if (args[i][0] == '\'' && args[i][1] == '\'')
			args[i][0] = '\0';
		else
		{
			while (args[i][j])
			{
				if (args[i][j] == '\'' && args[i][j + 1] == '#')
				{
					char *tmp = malloc((j + 2) * sizeof(char));
					ft_strlcpy(tmp, args[i], j + 1);
					free(args[i]);
					args[i] = ft_strjoin(tmp, data->subb[t]);
					t++;
				}
				j++;
			}
		}
		i++;
	}
}
