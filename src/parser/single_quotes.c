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

//When quotes check if quotes are closed
//If not closed, wait for closing quote
// check for expansions passed in seccond argument

int is_even(char *str, char c)
{
    int count = 0;
    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
	if ((count/2) % 2 == 0)
		return (0);
	return (count);
}

void rm_quotes(char *str)
{
	char *unquoted;

	if (ft_strchr(str, '\'') == NULL) //If no quotes, return
		return;
	unquoted = ft_strtrim(str, "'");
//	printf(GRN "removed quotes: %s\n" RESET, unquoted);
	free(str);
	str = ft_strdup(unquoted);
	free(unquoted);
}

void rm_quotes_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i][0] == '\'')
			rm_quotes(arr[i]);
		arr++;
	}
}

void add_quotes_pair(char *args)
{
	char *quoted;

	quoted = ft_strjoin("'", args);
	quoted = ft_strjoin(quoted, "'");
	//printf(BLU "added quotes: %s\n" RESET, quoted);
	free(args);
	args = ft_strdup(quoted);
	free(quoted);
}

void sin_quotes(char *args)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (ft_strchr(args, '\'') == NULL) //If no quotes, return
		return;
	else
	{
		// Check if quotes are closed
		// Check for number of pairs, if number of pairs is impair keep 1 pair
		if(is_even(args, '\'') == 0 || ft_strchr(args, '$') == NULL)
			rm_quotes(args);
		else
		{
				rm_quotes(args);
				add_quotes_pair(args);
		}
	}
	//printf(GRN "it stays: %s\n" RESET, args);
}