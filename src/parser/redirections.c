#include "minishell.h"

int is_redir(char *str)
{
    return (ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0);
}

void redirect_assign(t_cmd *current)
{
    int i = 0;
    while (current->args[i])
    {
        if (ft_strcmp(current->args[i], ">") == 0)
        {
            current->redirect_out = open(current->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            i++;
        }
        else if (ft_strcmp(current->args[i], "<") == 0)
        {
            current->redirect_in = open(current->args[i + 1], O_RDONLY);
            i++;
        }
        else if (ft_strcmp(current->args[i], ">>") == 0)
        {
            current->redirect_out = open(current->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            i++;
        }
		else if (ft_strcmp(current->args[i], "<<") == 0)
		{
			read_heredoc(current->args[i + 1], current);
		}
        i++;
    }
}

void    redirect_fd_dup(t_cmd *current)
{
    if (current->redirect_in != -1)
    {
        if (dup2(current->redirect_in, STDIN) == -1)
            handle_error("dup2 error redirect_in");
        close(current->redirect_in);
    }
    if (current->redirect_out != -1)
    {
        if (dup2(current->redirect_out, STDOUT) == -1)
            handle_error("dup2 error redirect_out");
        close(current->redirect_out);
    }
}