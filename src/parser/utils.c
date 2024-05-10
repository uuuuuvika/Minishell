#include "minishell.h"

void sub_dub_quotes(char *line_copy, t_data *data)
{
    char str[20];
    int index = 0;
    int count_subs = 0;

    while (line_copy[index])
    {
        if (line_copy[index] == '"')
            count_subs++;
        index++;
    }

    data->sub = malloc((count_subs / 2) * sizeof(char *));

    int s_index = 0;
    index = 0;
    while (line_copy[index])
    {
        if (line_copy[index] == '"')
        {
            int str_index = 0;
            while (line_copy[++index] != '"')
            {
                str[str_index++] = line_copy[index];
                line_copy[index] = '*';
            }
            str[str_index] = '\0';
            data->sub[s_index++] = strdup(str);
        }
        index++;
    }
    data->sub[s_index] = NULL;
}

int is_redir(char *str)
{
    return (ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">>") == 0);
}

int cnt_args(char **args)
{
    int i = 0;
    while (args[i] && !is_redir(args[i]))
        i++;
    return (i);
}

void pipe_assign(t_cmd *head)
{
    t_cmd *current = head;
    t_cmd *previous = NULL;
    while (current)
    {
        if (previous)
        {
            int p[2];
            pipe(p);
            previous->pipe_out = p[PIPE_WRITE];
            current->pipe_in = p[PIPE_READ];
        }
        previous = current;
        current = current->next;
    }
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
        i++;
    }
}