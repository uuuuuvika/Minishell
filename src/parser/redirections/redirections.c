#include "minishell.h"

int redirect_assign(t_cmd *current, t_data *data)
{
    int i = 0;
    int result;

    while (current->args[i])
    {
        if (ft_strcmp(current->args[i], ">") == 0)
        {
            result = process_redirection(current, &i, O_WRONLY | O_CREAT | O_TRUNC, 1);
            if (result != 0) return result;
        }
        else if (ft_strcmp(current->args[i], "<") == 0)
        {
            result = process_redirection(current, &i, O_RDONLY, 0);
            if (result != 0) return result;
        }
        else if (ft_strcmp(current->args[i], ">>") == 0)
        {
            result = process_redirection(current, &i, O_WRONLY | O_CREAT | O_APPEND, 1);
            if (result != 0) return result;
        }
        else if (ft_strcmp(current->args[i], "<<") == 0)
        {
            read_heredoc(current->args[i + 1], current, data);
            i++;
        }
        i++;
    }
    return 0;
}
