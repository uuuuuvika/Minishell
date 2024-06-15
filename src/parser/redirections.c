#include "minishell.h"

int is_redirect(char *str)
{
    return (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 1) == 0);
}

void redirect_assign(t_cmd *current, t_data *data)
{
    int i;

    i = 0;
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
            read_heredoc(current->args[i + 1], current, data);
        i++;
    }
}

void redirect_fd_dup(t_cmd *current, t_data *data)
{
    //printf("here_doc: %d\n", data->cmn_here_doc);
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
    if(data->cmn_here_doc != 0)
    {
        if (dup2(data->cmn_here_doc, STDOUT) == -1)
            handle_error("dup2 error here_doc");
        close(data->cmn_here_doc);
    }
}
