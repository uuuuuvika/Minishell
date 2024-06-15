#include "minishell.h"

int cnt_args(char **args)
{
    int i = 0;
    while (args[i] && !is_redirect(args[i]))
        i++;
    return (i);
}

void pipe_assign(t_cmd *command)
{
    int p[2];
    t_cmd *current = command;
    t_cmd *previous = NULL;
    while (current)
    {
        if (previous)
        {
            pipe(p);
            previous->pipe_out = p[PIPE_WRITE];
            current->pipe_in = p[PIPE_READ];
        }
        previous = current;
        current = current->next;
    }
}

