#include "minishell.h"

// int sub_quotes(char *input, t_data *data)
// {
//     return (sub_dub_quotes(input, data) || sub_sin_quotes(input, data));
// }


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
        //char *del = "\"";
        read_heredoc_simple(del, data);
        return 1;
    }
    return (0);
}