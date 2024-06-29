#include "minishell.h"

int sub_quotes(char *line_copy, t_data *data)
{
    if (sub_dub_quotes(line_copy, data) || sub_sin_quotes(line_copy, data))
    {
        free(line_copy);
        return (1);
    }
    return (0);
}