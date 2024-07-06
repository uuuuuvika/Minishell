#include "minishell.h"

int is_redirect(char *str)
{
    return (ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0);
}

int handle_redirection(const char *f, int flags, t_cmd *current, int is_out)
{
    int result = open_file(f, flags, current, is_out);
    return result;
}

int process_redirection(t_cmd *current, int *index, int flags, int is_out)
{
    int result = handle_redirection(current->args[*index + 1], flags, current, is_out);
    if (result != 0)
        return result;
    (*index)++;
    return 0;
}
