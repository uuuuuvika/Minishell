#include "minishell.h"

int count_quotes(char *line_copy, char *del)
{
    int count_subs = 0;
    while (*line_copy)
    {
        if (*line_copy == *del)
            count_subs++;
        line_copy++;
    }
    return (count_subs);
}

int handle_odd_quotes(int count_subs, t_data *data, char *del)
{
    if (count_subs % 2 != 0)
    {
        read_heredoc_simple(del, data);
        return 1;
    }
    return (0);
}

int word_len(char *line_copy, int start, char *del)
{
    int i;

    i = start;
    while (line_copy[++i] != *del)
        ;
    return i - start;
}

void handle_empty_quotes(char *arg, char *del)
{
    if (arg[0] == *del && arg[1] == *del)
    {
        arg[0] = '\0';
    }
}

void replace_substring(char **arg, int j, char *sub)
{
    char *tmp = malloc((j + 2) * sizeof(char));
    ft_strlcpy(tmp, *arg, j + 1);
    free(*arg);
    *arg = ft_strjoin(tmp, sub);
    free(tmp);
}
