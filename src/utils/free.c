#include "minishell.h"

void free_arr2D(char **arr2D)
{
    int i;

    i = 0;
    while (arr2D[i] != NULL && arr2D[i][0] != '\n') // '\n' is a delimiter for the end of the array????
        free(arr2D[i++]);
    free(arr2D);
}

void free_data(t_data *data)
{
    t_cmd *current;
    t_cmd *next;

    current = data->commands;
    while (current->next != NULL)
    {
        next = current->next;
        free_arr2D(current->args);
        free(current);
        current = next;
    }	
}

// void free_command(t_cmd *command)
// {
//     free_arr2D(command->args);
//     free(command);
// }

// void free_commands(t_cmd *commands)
// {
//     t_cmd *tmp;

// 	while (commands)
// 	{
// 		tmp = commands;
// 		commands = commands->next;
// 		free_command(tmp);
// 	}	
// }