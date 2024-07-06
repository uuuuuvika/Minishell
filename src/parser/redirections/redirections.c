#include "minishell.h"

int is_redirect(char *str)
{
    return (ft_strcmp(str, ">") == 0 
    || ft_strcmp(str, "<") == 0 
    || ft_strcmp(str, ">>") == 0
    || ft_strcmp(str, "<<") == 0);
}

int redirect_assign(t_cmd *current, t_data *data)
{
    int i;

    i = 0;
    while (current->args[i])
    {
        if (ft_strcmp(current->args[i], ">") == 0)
        {
            current->redirect_out = open(current->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (current->redirect_out == -1)
            {
               // write_error("minishell: ");
                if (current->args[i + 1])
                {
                    write_error_arg(current->args[i + 1], ERR_NO_FILE);
                    return (1);
                }
                write_error(ERR_SYNTAX);
                return (2);
            }
            i++;
        }
        else if (ft_strcmp(current->args[i], "<") == 0)
        {
            current->redirect_in = open(current->args[i + 1], O_RDONLY);
            if (current->redirect_in == -1)
            {
               // write_error("minishell: ");
                if (current->args[i + 1])
                {
                    write_error_arg(current->args[i + 1], ERR_NO_FILE);
                    return (1);
                }
                write_error(ERR_SYNTAX);
                return (2);
            }
            i++;
        }
        else if (ft_strcmp(current->args[i], ">>") == 0)
        {
            current->redirect_out = open(current->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (current->redirect_out == -1)
            {
                //write_error("minishell: ");
                if (current->args[i + 1])
                {
                    write_error_arg(current->args[i + 1], ERR_NO_FILE);
                    return (1);
                }
                write_error(ERR_SYNTAX);
                return (2);
            }
            i++;
        }
        else if (ft_strcmp(current->args[i], "<<") == 0){
                read_heredoc(current->args[i + 1], current, data);
                i++;
        }
        i++;
    }
    return (0);
}
