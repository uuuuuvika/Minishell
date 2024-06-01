#include "minishell.h"

// ech"o" hi = hi
// ech"o" h''i = hi
// [1:02 PM] plandolf
// ech"o" h'""'i = h""i
// [1:02 PM] plandolf
// ech"o" h"'""'"i = h''i
// e''ch"o" h"'""'"i = h''i
// [1:05 PM] plandolf
// e' 'ch"o" h"'""'"i = command not found
// e" "ch"o" h"'""'"i = command not found
// 'ech"o"' h"'""'"i = not found
// 'ech"'o'"' h"'""'"i = not found
// 'ech'o'' h"'""'"i = h''i
// ''ech'o''' h"'""'"i = h''i
// ARG= ho
// ec$ARG hi = hi
// ec$ARG $A''RG = RG :cara_pensativa::cara_pensativa::cara_pensativa:
// [1:05 PM] plandolf
// ec$A''RG hi = ecRG: command not found

void sub_sin_quotes(char *line_copy, t_data *data)
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
		return;
	}

	data->subb = malloc((count_subs / 2) * sizeof(char *));
	int s_index = 0;
	index = 0;
	while (line_copy[index])
	{
		if (line_copy[index] == '\'')
		{
			int k = index;
            while (line_copy[++k] != '"')
                ;
            int len = k - index;
            char *str = calloc(len, sizeof(char));
			int str_index = 0;
			while (line_copy[++index] != '\'')
			{
				str[str_index++] = line_copy[index];
				line_copy[index] = '#';
			}
			data->subb[s_index++] = ft_strdup(str);
		}
		index++;
	}
	data->subb[s_index] = NULL;
}

void return_sin_quotes(char **args, t_data *data)
{
	int i = 0;
	int t = 0;
	while (args[i])
	{
		int j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\'' && args[i][j + 1] == '#')
			{
				free(args[i]);
				args[i] = ft_strdup(data->subb[t]);
				t++;
			}
			else if (args[i][j] == '\'' && args[i][j + 1] == '\'')
				args[i][j] = '\0';
			j++;
		}
		i++;
	}
}
