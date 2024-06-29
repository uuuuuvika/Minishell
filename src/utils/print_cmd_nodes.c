#include "minishell.h"

void print_cmd_nodes(t_data *data)
{
    printf("num_of_children: %d\n", data->num_of_children);
    t_cmd *current = data->commands;
    while (current)
    {
        printf("cmd: %s\n", current->args[0]);
        printf("num_args: %d\n", current->num_args);
        for (int i = 0; current->args[i]; i++)
            printf("args[%d]: %s\n", i, current->args[i]);
        printf("pipe_in: %d\n", current->pipe_in);
        printf("pipe_out: %d\n", current->pipe_out);
        printf("here_doc: %d\n", current->here_doc);
        printf("redirect_in: %d\n", current->redirect_in);
        printf("redirect_out: %d\n", current->redirect_out);
        printf("\n");
        current = current->next;
    }
}