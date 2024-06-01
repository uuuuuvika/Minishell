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

// void rm_quotes(char *str)
// {
//     int len = ft_strlen(str);
//     if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
// 	{
//         ft_memmove(str, str + 1, len - 2);
//         str[len - 2] = '\0';
//     }
// }

// When quotes check if quotes are closed
// If not closed, wait for closing quote
//  check for expansions passed in seccond argument

/*
Minishell > cat ''

Minishell > cat '""'
cat: '""': No such file or directory
Minishell > cat 'ggg'
cat: ggg: No such file or directory
Minishell > cat '"ggg"'
cat: '"***"': No such file or directory
Minishell > echo ''

Minishell > echo ""
""
Minishell > cat
fdfdfd
fdfdfd
fdfdf
fdfdf
Minishell > cat ""
cat: '""': No such file or directory
Minishell > cat ''

*/

void sub_sin_quotes(char *line_copy, t_data *data)
{
	char str[20];
	int index = 0;
	int count_subs = 0;

	while (line_copy[index])
	{
		if (line_copy[index] == '\'')
			count_subs++;
		index++;
	}
	// index = 0;

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
			int str_index = 0;
			while (line_copy[++index] != '\'')
			{
				str[str_index++] = line_copy[index];
				line_copy[index] = '#';
			}
			str[str_index] = '\0';
			data->subb[s_index++] = strdup(str);
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
