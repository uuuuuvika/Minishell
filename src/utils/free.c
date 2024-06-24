#include "minishell.h"

void free_arr2D(char **arr2D)
{
    int i;

    i = 0;
    while (arr2D[i] != NULL) // '\n' is a delimiter for the end of the array????
        free(arr2D[i++]);
    free(arr2D);
}

void free_data(t_data *data) // ls
{
    t_cmd *current;
    t_cmd *next;

    if (data->commands == NULL)
        return;
    current = data->commands;
    while (current->next != NULL)
    {
        next = current->next;
        free_arr2D(current->args);
        current->args = NULL;
        current->num_args = 0;
        current->pipe_in = 0;
        current->pipe_out = 0;
        current->here_doc = 0;
        current->here_doc_exp = 0;
        current->redirect_in = 0;
        current->redirect_out = 0;
        free(current);
        current = next;
    }
    free_arr2D(current->args);
    free(current);
    current = NULL;
    data->commands = NULL;

    data->num_of_children = 0;
    //free_arr2D(data->envs);
    free_arr2D(data->sub);
    free_arr2D(data->subb);
   // data->envs = NULL;
    data->sub = NULL;
    data->subb = NULL;
    data->cmn_here_doc = 0;
}
