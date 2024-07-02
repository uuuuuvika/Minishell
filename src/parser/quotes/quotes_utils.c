#include "minishell.h"

int sub_quotes(char *input, t_data *data)
{
    return (sub_dub_quotes(input, data) || sub_sin_quotes(input, data));
}