#include "minishell.h"

void free_arr2D(char **arr2D)
{
    int i;

    i = 0;
    while (arr2D[i] != NULL && arr2D[i][0] != '\n')
        free(arr2D[i++]);
    free(arr2D);
}

void free_command(t_cmd *command)
{
    free_arr2D(command->args);
    free(command);
}

void free_commands(t_cmd *commands)
{
    t_cmd *tmp;

    {
        tmp = commands;
        commands = commands->next;
        free_command(tmp);
        free_command(commands++);
    }
}

void free_data(t_data *data)
{
    // free_arr2D(data->envp);
    free_arr2D(data->sub);
    free_commands(data->commands);
}