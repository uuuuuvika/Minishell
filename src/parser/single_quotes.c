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

// int is_even(char *str, char c)
// {
// 	int count = 0;
// 	while (*str)
// 	{
// 		if (*str == c)
// 		{
// 			count++;
// 		}
// 		str++;
// 	}
// 	// if ((count/2) % 2 == 0)
// 	// 	return (0);
// 	return ((count / 2) % 2);
// }

// void rm_quotes(char *str)
// {
// 	char *unquoted;

// 	if (ft_strchr(str, '\'') == NULL) // If no quotes, return
// 		return;
// 	unquoted = ft_strtrim(str, "'");
// 	// printf(GRN "removed quotes: %s\n" RESET, unquoted);
// 	free(str);
// 	str = ft_strdup(unquoted);
// 	free(unquoted);
// }

// void rm_quotes_arr(char **arr)
// {
// 	int i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		if (arr[i][0] == '\'')
// 			rm_quotes(arr[i]);
// 		arr++;
// 	}
// }

// void add_quotes_pair(char *args)
// {
// 	char *quoted;

// 	quoted = ft_strjoin("'", args);
// 	quoted = ft_strjoin(quoted, "'");
// 	// printf(BLU "added quotes: %s\n" RESET, quoted);
// 	free(args);
// 	args = ft_strdup(quoted);
// 	free(quoted);
// }

// void sin_quotes(char *args, t_data *data)
// {
// 	if (ft_strchr(args, '\'') == NULL) // If no quotes, return
// 		return;
// 	else
// 	{
// 		// Check if quotes are closed
// 		// Check for number of pairs, if number of pairs is impair keep 1 pair
// 		if (is_even(args, '\'') || ft_strchr(args, '$') == NULL) {
// 			rm_quotes(args);
// 			sub_sin_quotes(args, data);
// 		}
// 		else
// 		{
// 			printf(RED "Error: quotes not closed\n" RESET);
// 			rm_quotes(args);
// 			// add_quotes_pair(args);
			
// 		}
// 	}
// 	// printf(GRN "it stays: %s\n" RESET, args);
// }

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
	index = 0;
	data->subb = malloc((count_subs / 2) * sizeof(char *));

	int s_index = 0;
	index = 0;
	while (line_copy[index])
	{
		if (line_copy[index] == '\'' && line_copy[index + 1] == '$')
		{
			int str_index = 0;
			str[str_index++] = '\'';
			while (line_copy[++index] != '\'')
			{
				str[str_index++] = line_copy[index];
				line_copy[index] = '#';
			}
			str[str_index++] = '\'';
			str[str_index] = '\0';
			data->subb[s_index++] = strdup(str);
		}
		else if (line_copy[index] == '\'' && line_copy[index + 1] != '$')
		{
			int str_index = 0;
			//str[str_index++] = '\'';
			while (line_copy[++index] != '\'')
			{
				str[str_index++] = line_copy[index];
				line_copy[index] = '#';
			}
			//str[str_index++] = '\'';
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
				//size_t len = ft_strlen(args[i]);
				//printf("len: %zu\n", len);
				//if (len == ft_strlen(data->subb[t]))
				//{
					//printf("sub: %s\n", data->subb[t]);
					free(args[i]);
					args[i] = ft_strdup(data->subb[t]);
					//printf("args: %s\n", args[i]);
					t++;
				//}
			}
			j++;
		}
		i++;
	}
}
